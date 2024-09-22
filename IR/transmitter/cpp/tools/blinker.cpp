#include "blinker.h"


void Blinker::Blink(int count)
{
	while (--count >= 0)
	{
		hw_if.set_led(1);
		hw_if.sleep_us(200000);
		hw_if.set_led(0);
		hw_if.sleep_us(200000);
	}
}