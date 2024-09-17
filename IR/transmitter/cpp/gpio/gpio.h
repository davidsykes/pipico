#pragma once
#include "../hw_if/ihardware_interface.h"

class GPIOInputPin
{
    int pin;
    IHardwareInterface& hw_if;
public:
    GPIOInputPin(int pin, IHardwareInterface& hw_if);
    void SetPullUp(int value);
    bool Value();
};

class GPIOOutputPin
{
    int pin;
    IHardwareInterface& hw_if;
public:
    GPIOOutputPin(int pin, IHardwareInterface& hw_if);
    void SetValue(bool value);
    uint64_t SetValueAt(bool value, uint64_t time_us);
};