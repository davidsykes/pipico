#include "hardware_interface.h"
#include "pico/cyw43_arch.h"

void _cyw43_arch_init()
{
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
    }
}

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

void _set_led(int value)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, value);
}

void _sleep_us(int useconds)
{
    sleep_us(useconds);
}

sHardwareInterface* create_hardware_interface()
{
    sHardwareInterface* hwif = calloc(1, sizeof(sHardwareInterface));

    hwif->cyw43_arch_init = &_cyw43_arch_init;
    hwif->initialise_input_pin = &_initialise_input_pin;
    hwif->initialise_output_pin = &_initialise_output_pin;
    hwif->gpio_get = &_gpio_get;
    hwif->gpio_put = &_gpio_put;
    hwif->set_led = &_set_led;
    hwif->sleep_us = &_sleep_us;

    return hwif;
}