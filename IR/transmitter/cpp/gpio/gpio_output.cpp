#include "gpio.h"


GPIOOutputPin::GPIOOutputPin(int pin, IHardwareInterface& hw_if) : hw_if(hw_if)
{
    this->pin = pin;
    hw_if.initialise_output_pin(pin);
}

void GPIOOutputPin::SetValue(int value)
{
    hw_if.gpio_put(pin, value);
}