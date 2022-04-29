#include <Arduino.h>

extern "C" {
	void arduino_serial_print(const char c[])
	{
		Serial.print(c);
	}
}
