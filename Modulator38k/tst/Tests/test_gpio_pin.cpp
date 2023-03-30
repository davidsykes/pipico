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

static int mock_gpio_get(int pin)
{
	if (pin == gpio_pin_number)
		return gpio_pin_value;
	return 999;
}

sSystem* create_mock_system()
{
	sSystem* system = (sSystem*)malloc(sizeof(sSystem));
	if (system != 0)
	{
		system->gpio_put = &mock_gpio_put;
		system->gpio_get = &mock_gpio_get;
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

void gpio_get_returns_the_pin_value()
{
	gpio_pin_number = 34;
	gpio_pin_value = 45;
	sSystem* mock_system = create_mock_system();
	sGPIOPin* pin = create_gpio_pin(mock_system, 34);

	int value = pin->gpio_get(pin);

	if (value != 45)
	{
		*((int*)0) = 0;
	}
}


void run_gpio_pin_tests()
{
	gpio_put_calls_system_gpio_put_with_value();
	gpio_get_returns_the_pin_value();
}