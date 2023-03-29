#include <stdlib.h>
#include "modulator.h"

void modulator_modulate(sModulator* this);

sModulator* create_modulator(sInputPin* input_pin, sPulser* pulsar)
{
    sModulator* modulator = malloc(sizeof(sModulator));
    if (modulator != 0)
    {
        modulator->modulate = &modulator_modulate;
        modulator->input_pin = input_pin;
        modulator->pulser = pulsar;
    }
    return modulator;
}


void modulator_modulate(sModulator* self)
{
    if (self->input_pin->gpio_get(self->input_pin) != 0)
    {
        self->pulser->pulse(self->pulser);
    }
}