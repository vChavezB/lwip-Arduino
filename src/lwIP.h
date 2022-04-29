#ifndef _ARDUINO_LWIP_H
#define _ARDUINO_LWIP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "src/include/lwip/init.h"
#include "src/include/lwip/ip4_addr.h"
#include "src/include/lwip/netif.h"
#include "src/include/lwip/dhcp.h"
#include "src/include/lwip/apps/httpd.h"
#include "src/include/lwip/apps/mqtt.h"
#include "src/include/lwip/apps/http_client.h"
#include "src/include/netif/ethernet.h"
#include "src/include/lwip/snmp.h"
#include "src/include/lwip/pbuf.h"
#include "src/include/lwip/err.h"
#include "src/include/lwip/timeouts.h"
#ifdef __cplusplus
}
#endif

#endif