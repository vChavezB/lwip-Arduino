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