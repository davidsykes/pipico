#include "pico/stdlib.h"
#include "stdio.h"

#include "pico/cyw43_arch.h"

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

int main_gpio()
{
    //stdio_init_all();
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    printf("round\n");
    int count = 5;
    while (count-- > 0) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
    }
    printf("rounded\n");

    int pin_number = 4;
    gpio_set_dir(pin_number, GPIO_IN);

    //_initialise_input_pin(3);
    int b = gpio_get(pin_number); //_gpio_get(3);
    printf("GPIO %d\n", b);
    while(1)
    {
        int c = gpio_get(pin_number); //_gpio_get(3);
        if (c != b)
        {
            b = c;
            printf("GPIO %d\n", b);
        }
    }

    // sSystem system;

    // system.initialise_input_pin = &_initialise_input_pin;
    // system.initialise_output_pin = &_initialise_output_pin;
    // system.gpio_get = &_gpio_get;
    // system.gpio_put = &_gpio_put;
    // system.sleep_us = &_sleep_us;

    // modulate(&system);
}