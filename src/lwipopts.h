/**
 * @file
 *
 * lwIP Options Configuration
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/**
  *  Portions Copyright (c) 2020, 2021 Analog Devices, Inc.
  */


#ifndef LWIPOPTS_H_
#define LWIPOPTS_H_

#ifndef PROCESSOR_LITTLE_ENDIAN
#define PROCESSOR_LITTLE_ENDIAN
#endif



/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#ifndef NO_SYS
#define NO_SYS                          1
#endif

#define LWIP_TIMERS 1

/*
 ------------------------------------
 ---------- Memory options ----------
 ------------------------------------
 */
/**
 * MEM_LIBC_MALLOC==1: Use malloc/free/realloc provided by your C-library
 * instead of the lwip internal allocator. Can save code size if you
 * already use it.
 */
#ifndef MEM_LIBC_MALLOC
#define MEM_LIBC_MALLOC                 1
#endif

/**
 * MEMP_MEM_MALLOC==1: Use mem_malloc/mem_free instead of the lwip pool allocator.
 * Especially useful with MEM_LIBC_MALLOC but handle with care regarding execution
 * speed and usage from interrupts!
 */
#ifndef MEMP_MEM_MALLOC
#define MEMP_MEM_MALLOC                 1
#endif

/**
 * MEM_ALIGNMENT: should be set to the alignment of the CPU
 *    4 byte alignment -> #define MEM_ALIGNMENT 4
 *    2 byte alignment -> #define MEM_ALIGNMENT 2
 */
#ifndef MEM_ALIGNMENT
#define MEM_ALIGNMENT                   4
#endif

/**
 * MEM_SIZE: the size of the heap memory. If the application will send
 * a lot of data that needs to be copied, this should be set high.
 */
#ifndef MEM_SIZE
#define MEM_SIZE                        (1522*4)
#endif

/**
 * MEMP_SEPARATE_POOLS: if defined to 1, each pool is placed in its own array.
 * This can be used to individually change the location of each pool.
 * Default is one big array for all pools
 */
#ifndef MEMP_SEPARATE_POOLS
#define MEMP_SEPARATE_POOLS             0
#endif

/**
 * MEMP_OVERFLOW_CHECK: memp overflow protection reserves a configurable
 * amount of bytes before and after each memp element in every pool and fills
 * it with a prominent default value.
 *    MEMP_OVERFLOW_CHECK == 0 no checking
 *    MEMP_OVERFLOW_CHECK == 1 checks each element when it is freed
 *    MEMP_OVERFLOW_CHECK >= 2 checks each element in every pool every time
 *      memp_malloc() or memp_free() is called (useful but slow!)
 */
#ifndef MEMP_OVERFLOW_CHECK
#define MEMP_OVERFLOW_CHECK             0
#endif

/**
 * MEMP_SANITY_CHECK==1: run a sanity check after each memp_free() to make
 * sure that there are no cycles in the linked lists.
 */
#ifndef MEMP_SANITY_CHECK
#define MEMP_SANITY_CHECK               1
#endif

/**
 * MEM_USE_POOLS==1: Use an alternative to malloc() by allocating from a set
 * of memory pools of various sizes. When mem_malloc is called, an element of
 * the smallest pool that can provide the length needed is returned.
 * To use this, MEMP_USE_CUSTOM_POOLS also has to be enabled.
 */
#ifndef MEM_USE_POOLS
#define MEM_USE_POOLS                   0
#endif

/**
 * MEM_USE_POOLS_TRY_BIGGER_POOL==1: if one malloc-pool is empty, try the next
 * bigger pool - WARNING: THIS MIGHT WASTE MEMORY but it can make a system more
 * reliable. */
#ifndef MEM_USE_POOLS_TRY_BIGGER_POOL
#define MEM_USE_POOLS_TRY_BIGGER_POOL   0
#endif

/**
 * MEMP_USE_CUSTOM_POOLS==1: whether to include a user file lwippools.h
 * that defines additional pools beyond the "standard" ones required
 * by lwIP. If you set this to 1, you must have lwippools.h in your
 * inlude path somewhere.
 */
#ifndef MEMP_USE_CUSTOM_POOLS
#define MEMP_USE_CUSTOM_POOLS           0
#endif

/**
 * Set this to 1 if you want to free PBUF_RAM pbufs (or call mem_free()) from
 * interrupt context (or another context that doesn't allow waiting for a
 * semaphore).
 * If set to 1, mem_malloc will be protected by a semaphore and SYS_ARCH_PROTECT,
 * while mem_free will only use SYS_ARCH_PROTECT. mem_malloc SYS_ARCH_UNPROTECTs
 * with each loop so that mem_free can run.
 *
 * ATTENTION: As you can see from the above description, this leads to dis-/
 * enabling interrupts often, which can be slow! Also, on low memory, mem_malloc
 * can need longer.
 *
 * If you don't want that, at least for NO_SYS=0, you can still use the following
 * functions to enqueue a deallocation call which then runs in the tcpip_thread
 * context:
 * - pbuf_free_callback(p);
 * - mem_free_callback(m);
 */
#ifndef LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT
#define LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT 0
#endif

#define SYS_LIGHTWEIGHT_PROT 0

#define LWIP_SOCKET 0
#define LWIP_COMPAT_SOCKETS 0
#define LWIP_NETCONN 0

/**
 * NO_SYS_NO_TIMERS==1: Drop support for sys_timeout when NO_SYS==1
 * Mainly for compatibility to old versions.
 */
 /** LWIP_TCPIP_TIMEOUT==1: Enable tcpip_timeout/tcpip_untimeout tod create
 * timers running in tcpip_thread from another thread.
 */
#ifndef LWIP_TCPIP_TIMEOUT
#define LWIP_TCPIP_TIMEOUT              1
#endif
#ifndef NO_SYS_NO_TIMERS
#define NO_SYS_NO_TIMERS                0
#endif


#define LWIP_TCP_KEEPALIVE 0

/*
 ------------------------------------------------
 ---------- Internal Memory Pool Sizes ----------
 ------------------------------------------------
 */
/**
 * MEMP_NUM_PBUF: the number of memp struct pbufs (used for PBUF_ROM and PBUF_REF).
 * If the application sends a lot of data out of ROM (or other static memory),
 * this should be set high.
 */
#ifndef MEMP_NUM_PBUF
#ifdef DEBUG
#define MEMP_NUM_PBUF                   4
#else
#define MEMP_NUM_PBUF                   8
#endif
#endif

/**
 * MEMP_NUM_RAW_PCB: Number of raw connection PCBs
 * (requires the LWIP_RAW option)
 */
#ifndef MEMP_NUM_RAW_PCB
#define MEMP_NUM_RAW_PCB                0
#endif

/**
 * MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
 * per active UDP "connection".
 * (requires the LWIP_UDP option)
 */
#ifndef MEMP_NUM_UDP_PCB
#define MEMP_NUM_UDP_PCB                3
#endif

/**
 * MEMP_NUM_TCP_PCB: the number of simulatenously active TCP connections.
 * (requires the LWIP_TCP option)
 */
#ifndef MEMP_NUM_TCP_PCB
#define MEMP_NUM_TCP_PCB                5
#endif

/**
 * MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP connections.
 * (requires the LWIP_TCP option)
 */
#ifndef MEMP_NUM_TCP_PCB_LISTEN
#define MEMP_NUM_TCP_PCB_LISTEN         3
#endif

/**
 * MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP segments.
 * (requires the LWIP_TCP option)
 */
#ifndef MEMP_NUM_TCP_SEG
#define MEMP_NUM_TCP_SEG                16
#endif

/**
 * MEMP_NUM_REASSDATA: the number of IP packets simultaneously queued for
 * reassembly (whole packets, not fragments!)
 */
#ifndef MEMP_NUM_REASSDATA
#define MEMP_NUM_REASSDATA              0
#endif

/**
 * MEMP_NUM_FRAG_PBUF: the number of IP fragments simultaneously sent
 * (fragments, not whole packets!).
 * This is only used with IP_FRAG_USES_STATIC_BUF==0 and
 * LWIP_NETIF_TX_SINGLE_PBUF==0 and only has to be > 1 with DMA-enabled MACs
 * where the packet is not yet sent when netif->output returns.
 */
#ifndef MEMP_NUM_FRAG_PBUF
#define MEMP_NUM_FRAG_PBUF              0
#endif

/**
 * MEMP_NUM_ARP_QUEUE: the number of simulateously queued outgoing
 * packets (pbufs) that are waiting for an ARP request (to resolve
 * their destination address) to finish.
 * (requires the ARP_QUEUEING option)
 */
#ifndef MEMP_NUM_ARP_QUEUE
#define MEMP_NUM_ARP_QUEUE              0
#endif

/**
 * MEMP_NUM_IGMP_GROUP: The number of multicast groups whose network interfaces
 * can be members et the same time (one per netif - allsystems group -, plus one
 * per netif membership).
 * (requires the LWIP_IGMP option)
 */
#ifndef MEMP_NUM_IGMP_GROUP
#define MEMP_NUM_IGMP_GROUP             0
#endif

/**
 * MEMP_NUM_SYS_TIMEOUT: the number of simulateously active timeouts.
 * (requires NO_SYS==0)
 */
#ifndef MEMP_NUM_SYS_TIMEOUT
#define MEMP_NUM_SYS_TIMEOUT            6
#endif

/**
 * MEMP_NUM_NETBUF: the number of struct netbufs.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#ifndef MEMP_NUM_NETBUF
#define MEMP_NUM_NETBUF                 0
#endif

/**
 * MEMP_NUM_NETCONN: the number of struct netconns.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#ifndef MEMP_NUM_NETCONN
#define MEMP_NUM_NETCONN                0
#endif

/**
 * MEMP_NUM_TCPIP_MSG_API: the number of struct tcpip_msg, which are used
 * for callback/timeout API communication.
 * (only needed if you use tcpip.c)
 */
#ifndef MEMP_NUM_TCPIP_MSG_API
#define MEMP_NUM_TCPIP_MSG_API          0
#endif

/**
 * MEMP_NUM_TCPIP_MSG_INPKT: the number of struct tcpip_msg, which are used
 * for incoming packets.
 * (only needed if you use tcpip.c)
 */
#ifndef MEMP_NUM_TCPIP_MSG_INPKT
#define MEMP_NUM_TCPIP_MSG_INPKT        0
#endif

/**
 * MEMP_NUM_SNMP_NODE: the number of leafs in the SNMP tree.
 */
#ifndef MEMP_NUM_SNMP_NODE
#define MEMP_NUM_SNMP_NODE              0
#endif

/**
 * MEMP_NUM_SNMP_ROOTNODE: the number of branches in the SNMP tree.
 * Every branch has one leaf (MEMP_NUM_SNMP_NODE) at least!
 */
#ifndef MEMP_NUM_SNMP_ROOTNODE
#define MEMP_NUM_SNMP_ROOTNODE          0
#endif

/**
 * MEMP_NUM_SNMP_VARBIND: the number of concurrent requests (does not have to
 * be changed normally) - 2 of these are used per request (1 for input,
 * 1 for output)
 */
#ifndef MEMP_NUM_SNMP_VARBIND
#define MEMP_NUM_SNMP_VARBIND           0
#endif

/**
 * MEMP_NUM_SNMP_VALUE: the number of OID or values concurrently used
 * (does not have to be changed normally) - 3 of these are used per request
 * (1 for the value read and 2 for OIDs - input and output)
 */
#ifndef MEMP_NUM_SNMP_VALUE
#define MEMP_NUM_SNMP_VALUE             0
#endif

/**
 * MEMP_NUM_NETDB: the number of concurrently running lwip_addrinfo() calls
 * (before freeing the corresponding memory using lwip_freeaddrinfo()).
 */
#ifndef MEMP_NUM_NETDB
#define MEMP_NUM_NETDB                  0
#endif

/**
 * MEMP_NUM_LOCALHOSTLIST: the number of host entries in the local host list
 * if DNS_LOCAL_HOSTLIST_IS_DYNAMIC==1.
 */
#ifndef MEMP_NUM_LOCALHOSTLIST
#define MEMP_NUM_LOCALHOSTLIST          0
#endif

/**
 * MEMP_NUM_PPPOE_INTERFACES: the number of concurrently active PPPoE
 * interfaces (only used with PPPOE_SUPPORT==1)
 */
#ifndef MEMP_NUM_PPPOE_INTERFACES
#define MEMP_NUM_PPPOE_INTERFACES       0
#endif

/**
 * PBUF_POOL_SIZE: the number of buffers in the pbuf pool.
 */
#ifndef PBUF_POOL_SIZE
#define PBUF_POOL_SIZE                  4
#endif
#define PBUF_POOL_BUFSIZE 1700
#define PBUF_LINK_HLEN 16

#define ARP_TABLE_SIZE 10
#define ARP_QUEUEING 1

#define ICMP_TTL 255

#define IP_OPTIONS 0
#define IP_FORWARD 0
#define IP_REASSEMBLY 1
#define IP_FRAG 1
#define IP_REASS_MAX_PBUFS 128
#define IP_FRAG_MAX_MTU 1500
#define IP_DEFAULT_TTL 255
#define LWIP_CHKSUM_ALGORITHM 3

#define LWIP_UDP 1
#define UDP_TTL 255

#define LWIP_TCP 1
/**
 * TCP_MSS: TCP Maximum segment size. (default is 536, a conservative default,
 * you might want to increase this.)
 * For the receive side, this MSS is advertised to the remote side
 * when opening a connection. For the transmit size, this MSS sets
 * an upper limit on the MSS advertised by the remote host.
 */
#ifndef TCP_MSS
#define TCP_MSS                        536
#endif

/**
 * TCP_SND_BUF: TCP sender buffer space (bytes).
 */
#ifndef TCP_SND_BUF
#define TCP_SND_BUF                     1500
#endif

#
/**
 * TCP_WND: The size of a TCP window.  This must be at least
 * (2 * TCP_MSS) for things to work well
 */
#ifndef TCP_WND
#define TCP_WND                         (4 * TCP_MSS)
#endif
#define TCP_TTL 255
/**
 * TCP_MAXRTX: Maximum number of retransmissions of data segments.
 */
#ifndef TCP_MAXRTX
#define TCP_MAXRTX                      12
#endif
/**
 * TCP_SYNMAXRTX: Maximum number of retransmissions of SYN segments.
 */
#ifndef TCP_SYNMAXRTX
#define TCP_SYNMAXRTX                   6
#endif
/**
 * TCP_QUEUE_OOSEQ==1: TCP will queue segments that arrive out of order.
 * Define to 0 if your device is low on memory.
 */
#ifndef TCP_QUEUE_OOSEQ
#define TCP_QUEUE_OOSEQ                 (LWIP_TCP)
#endif
/**
 * TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
 * as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work.
 */
#ifndef TCP_SND_QUEUELEN
#define TCP_SND_QUEUELEN                ((4 * (TCP_SND_BUF) + (TCP_MSS - 1))/(TCP_MSS))
#endif


#ifndef LWIP_NETIF_HOSTNAME
#define LWIP_NETIF_HOSTNAME 1
#endif
/*
 ---------------------------------
 ---------- RAW options ----------
 ---------------------------------
 */
/**
 * LWIP_RAW==1: Enable application layer to hook into the IP layer itself.
 */
#ifndef LWIP_RAW
#define LWIP_RAW                0
#endif

#define CHECKSUM_GEN_TCP 	1
#define CHECKSUM_GEN_UDP 	1
#define CHECKSUM_GEN_IP  	1
#define CHECKSUM_CHECK_TCP      1
#define CHECKSUM_CHECK_UDP      1
#define CHECKSUM_CHECK_IP 	1

/**
 * MEMP_NUM_FRAG_PBUF: the number of IP fragments simultaneously sent
 * (fragments, not whole packets!).
 * This is only used with IP_FRAG_USES_STATIC_BUF==0 and
 * LWIP_NETIF_TX_SINGLE_PBUF==0 and only has to be > 1 with DMA-enabled MACs
 * where the packet is not yet sent when netif->output returns.
 */
#ifndef MEMP_NUM_FRAG_PBUF
#define MEMP_NUM_FRAG_PBUF              0
#endif
#define IP_OPTIONS_ALLOWED 0

#ifndef TCP_OVERSIZE
#define TCP_OVERSIZE                    TCP_MSS
#endif

#define LWIP_DHCP                       1
#define DHCP_DOES_ARP_CHECK             1
#define LWIP_DEBUG LWIP_DBG_OFF         1
#define CONFIG_LINKSPEED_AUTODETECT     1


#define LWIP_NUMBER_OF_PARALLEL_HTTPD_SSI_CONNECTIONS 4
#define HTTPD_USE_CUSTOM_FSDATA                       1
#define LWIP_HTTPD_SUPPORT_11_KEEPALIVE               1
#define HTTPD_FSDATA_FILE                             "fsdata.c"
#define LWIP_HTTPD_DYNAMIC_HEADER                       1
#define LWIP_HTTPD_SSI                                1
#define LWIP_HTTPD_SSI_INCLUDE_TAG                    1
#define LWIP_HTTPD_MAX_TAG_NAME_LEN                   8
#define LWIP_HTTPD_MAX_TAG_INSERT_LEN                 4096
#define LWIP_HTTPD_SSI_RAW                            1

#define HTTPD_USE_MEM_POOL                            1
#define LWIP_HTTPD_ABORT_ON_CLOSE_MEM_ERROR           1
#define LWIP_HTTPD_KILL_OLD_ON_CONNECTIONS_EXCEEDED   1
#define HTTPD_MAX_WRITE_LEN(pcb)                      (TCP_MSS*4)
#define MEMP_NUM_PARALLEL_HTTPD_CONNS                 LWIP_NUMBER_OF_PARALLEL_HTTPD_SSI_CONNECTIONS
#define MEMP_NUM_PARALLEL_HTTPD_SSI_CONNS             LWIP_NUMBER_OF_PARALLEL_HTTPD_SSI_CONNECTIONS
#endif
