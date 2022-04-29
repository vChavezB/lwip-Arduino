#ifndef _ARDUINO_SYS_ARCH_H
#include <stdint.h>
/*

TODO: If using this Arduino lwIP port library 
with an OS, define the following datatypes

#define sys_mutex_t
#define sys_sem_t
#define sys_mbox_t
#define sys_thread_t

In addition sys_arch.c must be provided 

check 
https://www.nongnu.org/lwip/2_0_x/group__sys__os.html
https://www.nongnu.org/lwip/2_0_x/group__sys__time.html
https://www.nongnu.org/lwip/2_0_x/group__sys__prot.html

and this for summary
https://www.nongnu.org/lwip/2_0_x/group__sys__layer.html


*/
#define LWIP_PROVIDE_ERRNO

void sys_printf(const char *format, ...);

#endif //_ARDUINO_SYS_ARCH_H