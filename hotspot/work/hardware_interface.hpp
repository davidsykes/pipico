#pragma once

#include "hardware_interface.h"

class IHardwareInterface
{
public:
    virtual void initialise_input_pin(int pin_number)=0;
    virtual void initialise_output_pin(int pin_number)=0;
    virtual int gpio_get(int pin_number)=0;
    virtual void gpio_put(int pin_number, int value)=0;
    virtual void set_led(bool value)=0;
    virtual void sleep_us(int useconds)=0;
};


class PicoHardwareInterface : public IHardwareInterface
{
    sHardwareInterface* hardware_interface;

    virtual void initialise_input_pin(int pin_number);
    virtual void initialise_output_pin(int pin_number);
    virtual int gpio_get(int pin_number);
    virtual void gpio_put(int pin_number, int value);
    virtual void set_led(bool value);
    virtual void sleep_us(int useconds);

public:
    PicoHardwareInterface();
};
