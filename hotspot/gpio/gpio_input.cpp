#include "gpio.h"



GPIOInputPin::GPIOInputPin(int pin, IHardwareInterface& hw_if) : hw_if(hw_if)
{
    this->pin = pin;
    hw_if.initialise_input_pin(pin);
}

bool GPIOInputPin::Value()
{
    return hw_if.gpio_get(pin);
}