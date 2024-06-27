#include "gpio.h"



GPIOInputPin::GPIOInputPin(int pin, IHardwareInterface& hw_if) : hw_if(hw_if)
{
    this->pin = pin;
}

bool GPIOInputPin::Value()
{
    return false;
}