#include "pico/stdlib.h"
#include "modulate.h"

void _initialise_input_pin(int pin_number)
{
     gpio_init(pin_number);
     gpio_set_dir(pin_number, GPIO_IN);
}

void _initialise_output_pin(int pin_number)
{
     gpio_init(pin_number);
     gpio_set_dir(pin_number, GPIO_OUT);
}

int _gpio_get(int pin_number)
{
    return gpio_get(pin_number);
}

void _gpio_put(int pin_number, int value)
{
    gpio_put(pin_number, value);
}

void _sleep_us(int useconds)
{
    sleep_us(useconds);
}

int main()
{
    sSystem system;

    system.initialise_input_pin = &_initialise_input_pin;
    system.initialise_output_pin = &_initialise_output_pin;
    system.gpio_get = &_gpio_get;
    system.gpio_put = &_gpio_put;
    system.sleep_us = &_sleep_us;

    modulate(&system);
}