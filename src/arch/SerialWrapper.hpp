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
#ifndef _ARDUINO_SERIAL_WRAPPER_H
#define _ARDUINO_SERIAL_WRAPPER_H

#ifdef __cplusplus
extern "C" 
{
#endif //__cplusplus

void arduino_serial_print(const char c[]);


#ifdef __cplusplus
}
#endif //__cplusplus
#endif //_ARDUINO_SERIAL_WRAPPER_H
