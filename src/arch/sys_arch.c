#include "sys_arch.h"
#include <Arduino.h>
#include "SerialWrapper.hpp"
#include <stdarg.h>

#ifndef NOSYS

/*
  TODO: Here should be the OS implementation
*/

#endif

uint32_t sys_now(void)
{
  return millis();
}

void sys_printf(const char *format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    arduino_serial_print(buffer);
}