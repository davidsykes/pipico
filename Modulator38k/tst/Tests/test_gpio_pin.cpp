#include <stdlib.h>
extern "C"
{
#include "system.h"
#include "gpio_pin.h"
}

int gpio_pin_number;
int gpio_pin_value;

static void mock_gpio_put(int pin, int value)
{
	gpio_pin_number = pin;
	gpio_pin_value = value;
}

sSystem* create_mock_system()
{
	sSystem* system = (sSystem*)malloc(sizeof(sSystem));
	if (system != 0)
	{
		system->gpio_put = &mock_gpio_put;
	}
	return system;
}

void gpio_put_calls_system_gpio_put_with_value()
{
	sSystem* mock_system = create_mock_system();
	sGPIOPin* pin = create_gpio_pin(mock_system, 12);

	pin->gpio_put(pin, 23);

	if (gpio_pin_number != 12 && gpio_pin_value != 23)
	{
		*((int*)0) = 0;
	}
}


void run_gpio_pin_tests()
{
	gpio_put_calls_system_gpio_put_with_value();
}