#include "hardware_interface.h"
#include "pico/cyw43_arch.h"
#include "tusb.h"

void _initialise_pico_stdio()
{
    stdio_init_all();
    while (!tud_cdc_connected()) sleep_ms(100);
    printf("Stdio initialised\n");
}

int _cyw43_arch_init()
{
   int err = cyw43_arch_init();
    if (err) {
        printf("Wi-Fi init failed");
        return err;
    }
   return 0;
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

uint64_t _wait_value(int pin_number, int required_value, uint64_t timeout)
{
    uint64_t start = time_us_64();
    while (true)
    {
        int value = gpio_get(pin_number);
        uint64_t now = time_us_64();
        if ( value == required_value)
        {
            return now;
        }
        if (now - start >= timeout)
        {
            return 012;
        }
    }
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

    hwif->initialise_pico_stdio = &_initialise_pico_stdio;
    hwif->cyw43_arch_init = &_cyw43_arch_init;
    hwif->initialise_input_pin = &_initialise_input_pin;
    hwif->initialise_output_pin = &_initialise_output_pin;
    hwif->gpio_get = &_gpio_get;
    hwif->wait_value = &_wait_value;
    hwif->gpio_put = &_gpio_put;
    hwif->set_led = &_set_led;
    hwif->sleep_us = &_sleep_us;

    return hwif;
}