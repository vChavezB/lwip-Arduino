#include "sys_arch.h"
#include <Arduino.h>

#ifndef NOSYS

/*
  TODO: Here should be the OS implementation
*/

#endif

uint32_t sys_now(void)
{
  return millis();
}
