#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "pico/cyw43_arch.h"

#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1

char get_pins()
{
    return (char)(gpio_get_all() >> 8);
}

int main()
{
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }
//    while (true) {
//        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
//        sleep_ms(250);
//        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
//        sleep_ms(250);
//    }

    uart_init(UART_ID, BAUD_RATE);
    uart_putc(UART_ID, 'x');

    char current_pins = 42;

    while(1)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        uart_puts(UART_ID, "Waiting");
        char new_pins;
        do
        {
            new_pins = get_pins();
        } while (new_pins == current_pins);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

        current_pins = new_pins;
        long start_time = time_us_64();
        long current_time = start_time;
        long end_time = start_time + 1000000;

        do
        {
            current_time = time_us_64();
            new_pins = get_pins();
            if (new_pins != current_pins)
            {
                current_pins = new_pins;
                uart_putc_raw(UART_ID, current_pins);
            }

        } while (current_time < end_time);
        
        uart_puts(UART_ID, "Stop");
    }
}
