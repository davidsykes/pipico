#include <stdlib.h>
#include "gpio_pin.h"

static void gpio_pin_gpio_put(sGPIOPin* self, int value)
{
    self->system->gpio_put(self->pin_number, value);
}

sGPIOPin* create_gpio_pin(sSystem* system, int pin_number)
{
    sGPIOPin* pin = malloc(sizeof(sGPIOPin));
    if (pin != 0)
    {
        pin->system = system;
        pin->pin_number = pin_number;
        pin->gpio_put = &gpio_pin_gpio_put;
    }
    return pin;
}