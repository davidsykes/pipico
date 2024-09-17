#include "gpio.h"


GPIOOutputPin::GPIOOutputPin(int pin, IHardwareInterface& hw_if) : hw_if(hw_if)
{
    this->pin = pin;
    hw_if.initialise_output_pin(pin);
}

void GPIOOutputPin::SetValue(bool value)
{
    hw_if.gpio_put(pin, value);
}

uint64_t GPIOOutputPin::SetValueAt(bool value, uint64_t time_us)
{
    return hw_if.gpio_put_at_us(pin, value, time_us);
}