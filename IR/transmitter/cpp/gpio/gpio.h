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

class IGPIOOutputPin
{
public:
    virtual void SetValue(bool value) = 0;
    virtual uint64_t SetValueAt(bool value, uint64_t time_us) = 0;
};

class GPIOOutputPin : public IGPIOOutputPin
{
    virtual void SetValue(bool value);
    virtual uint64_t SetValueAt(bool value, uint64_t time_us);

    int pin;
    IHardwareInterface& hw_if;
public:
    GPIOOutputPin(int pin, IHardwareInterface& hw_if);
};