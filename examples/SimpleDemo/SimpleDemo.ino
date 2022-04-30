/*
Copyright (C) 2022 Victor Chavez
This file is part of lwIP Arduino
lwIP Arduino is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
IOLink Device Generator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with IOLink Device Generator.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <Arduino.h>
#include <lwIP_Arduino.h>

constexpr bool static_ip = false;
constexpr uint16_t ETHERNET_MTU = 1500;
constexpr uint32_t NetIF_Speed_BPS = 10000000;
constexpr uint8_t MacAddr[6] = {1, 2, 3, 4, 5, 6};
constexpr unsigned MAX_FRAME_SIZE = 1518;  // packet size excluding FCS
constexpr unsigned MIN_FRAME_SIZE = 60;


unsigned constexpr MAX_RX_QUEUE = 5;

struct EthQueue
{
  uint8_t data[MAX_RX_QUEUE][MAX_FRAME_SIZE];
  uint16_t len[MAX_RX_QUEUE];
  uint32_t nRead;
  uint32_t nWrite;
};

EthQueue RXQueue __attribute__((aligned(4)));
netif netif;

void initRXQueue(EthQueue* RXQueue)
{
    RXQueue->nWrite = 0;
    RXQueue->nRead = 0;
}

//Saves RX ethernet frame to the buffer to be processed in the main loop
void writeRXQueue(EthQueue* RXQueue, const uint8_t *ethFrame, uint16_t lenEthFrame)
{
  if(lenEthFrame > MAX_FRAME_SIZE)
  {
    lenEthFrame = MAX_FRAME_SIZE;
  }
  memcpy(&RXQueue->data[RXQueue->nWrite] , ethFrame, lenEthFrame);
  RXQueue->len[RXQueue->nWrite] = lenEthFrame;
  RXQueue->nWrite++;
  RXQueue->nWrite %= MAX_RX_QUEUE;
}

pbuf * readRXQueue(EthQueue* RXQueue)
{
  if(RXQueue->nWrite != RXQueue->nRead)
  {
    const int ehtFrmLen = RXQueue->len[RXQueue->nRead];
    pbuf* p = pbuf_alloc(PBUF_RAW, MAX_FRAME_SIZE, PBUF_RAM);
    memcpy(reinterpret_cast<uint8_t*>(p->payload),
            &RXQueue->data[RXQueue->nRead][0],
            ehtFrmLen);
    RXQueue->nRead++;
    RXQueue->nRead %= MAX_RX_QUEUE;
    return p;
  }
  else
  {
    return nullptr;
  }
}


bool isUnicast(const uint8_t frame)
{
  return (frame & 0x01) == 0;
}

//Set this callback in link status IRQ of ethernet PHY
void LinkHandler(bool link_status)
{
  if(link_status == true)
  {
    netif_set_link_up(&netif);
  }
  else
  {
    netif_set_link_down(&netif);
  }
}

//Should be call inside PHY RX Ethernet IRQ
static void EthRX_Handler(const uint8_t * ethFrame, const uint16_t lenEthFrame)
{
  LINK_STATS_INC(link.recv);
  MIB2_STATS_NETIF_ADD(&netif, ifinoctets, lenEthFrame);
  if (isUnicast(ethFrame[0]))
  {
    MIB2_STATS_NETIF_INC(&netif, ifinucastpkts);
  }
  else
  {
    MIB2_STATS_NETIF_INC(&netif, ifinnucastpkts);
  }
  writeRXQueue(&RXQueue, ethFrame, lenEthFrame);
}

static err_t netif_output(struct netif *netif, struct pbuf *p)
{
 
  void * context = netif->state;
  uint16_t total_len = 0;
  char buf[MAX_FRAME_SIZE]; /* max packet size including VLAN excluding FCS */

  if (p->tot_len > sizeof(buf))
  {
    MIB2_STATS_NETIF_INC(netif, ifoutdiscards);
    return ERR_IF;
  }
  pbuf_copy_partial(p, buf, p->tot_len, 0);
  LINK_STATS_INC(link.xmit);
  MIB2_STATS_NETIF_ADD(netif, ifoutoctets, p->tot_len);

  if(p->tot_len < MIN_FRAME_SIZE) // Pad to minimum ETH size
  {
    total_len = MIN_FRAME_SIZE;
  }
  else
  {
    total_len = p->tot_len;
  }

  if (isUnicast(buf[0]))
  {
    MIB2_STATS_NETIF_INC(netif, ifoutucastpkts);
  }
  else
  {
    MIB2_STATS_NETIF_INC(netif, ifoutnucastpkts);
  }
  /*
  Ethernet MAC-PHY should send frame here
  PhyMACSend(buf,total_len);
  */
  return ERR_OK;
}

static err_t netif_init(struct netif *netif)
{
  netif->name[0] = 'e';
  netif->name[1] = '0';
  netif->linkoutput = netif_output;
  netif->output     = etharp_output;
  netif->mtu        = ETHERNET_MTU;
  netif->flags      = NETIF_FLAG_BROADCAST |
                      NETIF_FLAG_ETHARP |
                      NETIF_FLAG_ETHERNET |
                      NETIF_FLAG_IGMP |
                      NETIF_FLAG_MLD6 |
                      NETIF_FLAG_LINK_UP;
  netif->hostname = "MyHostName";
  MIB2_INIT_NETIF(netif, snmp_ifType_ethernet_csmacd, NetIF_Speed_BPS);
  SMEMCPY(netif->hwaddr, &MacAddr, sizeof(netif->hwaddr));
  netif->hwaddr_len = sizeof(netif->hwaddr);
  initRXQueue(&RXQueue);
  return ERR_OK;
}

void setup()
{
  Serial.begin(115200);
  ip4_addr_t ip, mask , gateway;
  IP4_ADDR(&ip, 192, 168, 142, 1);
  IP4_ADDR(&mask, 255, 255, 255, 0);
  IP4_ADDR(&gateway, 192, 168, 142, 1);
  void * context = nullptr;
  if( static_ip == true)
  {
    netif_add(&netif, &ip, &mask, &gateway, context, netif_init, ethernet_input);
    netif_set_default(&netif);
    netif_set_up(&netif);
  }
  else
  {
      netif_add(&netif,
                reinterpret_cast<ip4_addr_t *>(IPADDR_ANY),
                reinterpret_cast<ip4_addr_t *>(IPADDR_ANY),
                reinterpret_cast<ip4_addr_t *>(IPADDR_ANY),
                context,
                netif_init,
                ethernet_input);
      netif_set_default(&netif);
      netif_set_up(&netif);
      dhcp_start(&netif);
  }

}
uint32_t last_time = 0;
void loop()
{
  const uint32_t currentTime = millis();
  if(currentTime-last_time> 250)
  {
    last_time = currentTime;
    sys_check_timeouts();
  }

  pbuf *p = readRXQueue(&RXQueue);
  if (p != nullptr)
  {
    if (netif.input(p, &netif) != ERR_OK)
    {
      LWIP_DEBUGF(NETIF_DEBUG, ("IP input error\r\n"));
      pbuf_free(p);
      p = NULL;
    }
  }
}