#pragma once
#include "pins.h"
#include "pulser.h"

typedef struct sModulator
{
    void (*modulate)(struct sModulator* self);

    sInputPin* input_pin;
    sPulser* pulser;

} sModulator;



sModulator* create_modulator(sInputPin* input_pin, sPulser* pulser);