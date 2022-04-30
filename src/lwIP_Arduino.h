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
#ifndef _ARDUINO_LWIP_H
#define _ARDUINO_LWIP_H

#ifdef __cplusplus
extern "C" {
#endif

/*
  Including some of the most common headers from LWIP for easy access.
  As arduino build system cannot include library directories
  the user has to larger paths to find the includes
*/
#include "lwip/include/lwip/netif.h"
#include "lwip/include/lwip/init.h"
#include "lwip/include/lwip/ip4_addr.h"
#include "lwip/include/lwip/ip6_addr.h"
#include "lwip/include/lwip/dhcp.h"
#include "lwip/include/lwip/snmp.h"
#include "lwip/include/lwip/err.h"
#include "lwip/include/lwip/timeouts.h"
#include "lwip/include/netif/ethernet.h"

#ifdef __cplusplus
}
#endif

#endif