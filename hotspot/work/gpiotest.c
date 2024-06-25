#include "gpiotest.h"
#include "stdio.h"
#include "pico/cyw43_arch.h"

int main_gpio(sHardwareInterface* system)
{
    //stdio_init_all();
    // if (cyw43_arch_init()) {
    //     printf("Wi-Fi init failed");
    //     return -1;
    // }

    int count = 4;
    while (count-- > 0) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
    }

    int pin_number = 2;
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
}