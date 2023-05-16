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

void send_bytes(unsigned char *p, int n)
{
    for (int i = 0 ; i < n ; i++)
    {
        uart_putc_raw(UART_ID, p[i]);
    }
}

void send_uint64(uint64_t l)
{
    send_bytes((unsigned char*)&l, 8);
}

void send_data(uint64_t time, unsigned char pins)
{
    send_uint64(time);
    send_bytes(&pins, 1);
}

int main()
{
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    uart_putc_raw(UART_ID, 'A');
    uart_putc(UART_ID, 'B');
    uart_puts(UART_ID, " Hello, UART!\n");

    for (int p = 8 ; p <= 15 ; p++)
    {
        gpio_init(p);
        gpio_set_dir(p, GPIO_IN);
        gpio_pull_up(p);
    }    

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

        uint64_t start_time = time_us_64();
        uint64_t current_time = start_time;
        uint64_t end_time = start_time + 1000000;
        send_uint64(0x0102030405060708);
        send_uint64(0x01020304);
        send_uint64(0x0102030405060708);
        send_data(current_time-start_time, current_pins);

        current_pins = new_pins;
        do
        {
            current_time = time_us_64();
            new_pins = get_pins();
            //if (new_pins != current_pins)
            {
                current_pins = new_pins;
                send_data(current_time-start_time, current_pins);
            }

        } while (current_time < end_time);
        
        send_uint64(0x0807060504030201);
        uart_puts(UART_ID, "Stop");
    }
}
