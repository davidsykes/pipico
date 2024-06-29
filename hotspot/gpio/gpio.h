#pragma once
#include "hardware_interface.hpp"


class GPIOInputPin
{
    int pin;
    IHardwareInterface& hw_if;
public:
    GPIOInputPin(int pin, IHardwareInterface& hw_if);
    bool Value();
};