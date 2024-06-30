#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/malloc.h"
#include "hardware/uart.h"
#include "pico/cyw43_arch.h"

#define UART_ID uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define TRACE_COUNT 1000
#define ONE_SECOND 1000000

char get_pins()
{
    return (char)(gpio_get_all() >> 8);
}sHardwareInterface

void send_bytes(unsigned char *p, int n)
{
    for (int i = 0 ; i < n ; i++)
    {
        uart_putc_raw(UART_ID, p[i]);
        sleep_us(1000);
    }
}

void send_uint64(uint64_t l)
{
    send_bytes((unsigned char*)&l, 8);
}

void send_int(int i)
{
    send_bytes((unsigned char*)&i, 4);
}

void send_char(unsigned char i)
{
    send_bytes(&i, 1);
}

void send_all_data(unsigned int* times, unsigned char *values, int count)
{
    send_int(0x12345678);
    send_int(count);
    for (int i = 0 ; i < count ; i++)sHardwareInterface
    {
        send_int(times[i]);
        send_char(values[i]);
    }
   send_int(0x87654321);
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

    uart_puts(UART_ID, "Trace capture starting");

    for (int p = 8 ; p <= 15 ; p++)
    {
        gpio_init(p);
        gpio_set_dir(p, GPIO_IN);
        gpio_pull_up(p);
    }

    int trace_count = TRACE_COUNT;
    unsigned int* trace_times = malloc(trace_count * sizeof(unsigned int));
    unsigned char* trace_values = malloc(trace_count * sizeof(unsigned char));

    while(1)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

        char current_pins = get_pins();
        trace_times[0] = 0;
        trace_values[0] = current_pins;
        int current_trace = 1;

        char new_pins;
        do
        {
            new_pins = get_pins();
        }
        while (new_pins == current_pins);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

        uint64_t start_time = time_us_64();
        uint64_t current_time = start_time;
        uint64_t end_time = start_time + ONE_SECOND;

        current_pins = new_pins;
        do
        {
            current_time = time_us_64();
            new_pins = get_pins();
            if (new_pins != current_pins)
            {
                current_pins = new_pins;
                trace_times[current_trace] = (unsigned int)(current_time - start_time);
                trace_values[current_trace] = current_pins;
                current_trace++;
            }

        }
        while (current_time < end_time && current_trace < trace_count);

        send_all_data(trace_times, trace_values, current_trace);
    }
}
