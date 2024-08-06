#pragma once
#include "pico_hardware_interface.h"


class GPIOInputPin
{
    int pin;
    IHardwareInterface& hw_if;
public:
    GPIOInputPin(int pin, IHardwareInterface& hw_if);
    void SetPullUp(int value);
    bool Value();
};