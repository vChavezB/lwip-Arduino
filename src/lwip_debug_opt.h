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
#ifndef LWIP_DEBUG_OPT_H
#define LWIP_DEBUG_OPT_H

#define LWIP_DEBUG 1

#define NETIF_DEBUG LWIP_DBG_ON
#define DHCP_DEBUG LWIP_DBG_ON
#define UDP_DEBUG  LWIP_DBG_ON
#define MEMP_DEBUG LWIP_DBG_ON
#define MEM_DEBUG LWIP_DBG_ON
#define ICMP_DEBUG LWIP_DBG_ON

#endif