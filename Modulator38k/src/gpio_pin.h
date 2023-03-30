#pragma once
#include "system.h"

typedef struct sGPIOPin
{
    void (*gpio_put)(struct sGPIOPin* self, int value);
    int (*gpio_get)(struct sGPIOPin* self);

    sSystem* system;
    int pin_number;

} sGPIOPin;

sGPIOPin* create_gpio_pin(sSystem* system, int pin_number);