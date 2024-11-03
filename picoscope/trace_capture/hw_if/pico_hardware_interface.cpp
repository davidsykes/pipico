#include "pico_hardware_interface.h"
#include "pico/cyw43_arch.h"
#include "picow_tcp_client.h"

#define TCP_BUFFER_LENGTH   2048

uint64_t PicoHardwareInterface::get_time_us()
{
    return time_us_64();
}

void PicoHardwareInterface::initialise_input_pin(int pin_number)
{
     gpio_init(pin_number);
     gpio_set_dir(pin_number, GPIO_IN);
}

void PicoHardwareInterface::gpio_set_pull_up(int pin_number, int value)
{
    if (value == 0)
    {
        gpio_pull_down(pin_number);
    }
    else
    {
        gpio_pull_up(pin_number);
    }
}

int PicoHardwareInterface::get_pins()
{
    return gpio_get_all();
}

int PicoHardwareInterface::wait_pins_change(sPinsChangeData* pins_change_data, int mask, uint64_t timeout)
{
    while (true)
    {
        int value = get_pins() & mask;
        uint64_t now = time_us_64();
        if ( value != pins_change_data->current_value)
        {
            pins_change_data->new_value = value;
            pins_change_data->time_us = now;
            return 1;
        }
        if ((now - pins_change_data->time_us) >= timeout)
        {
            return 0;
        }
    }
}

void PicoHardwareInterface::set_led(bool value)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, value);
}

void PicoHardwareInterface::sleep_us(int useconds)
{
    sleep_us(useconds);
}

int PicoHardwareInterface::tcp_request(const char* server, unsigned int port, const char* request, std::string& response)
{
    #ifdef DEBUG_TCP_REQUEST
    printf("---TCP REQUEST---\n%s\n^^^\n", request);
    #endif
    char buffer[TCP_BUFFER_LENGTH];
    buffer[0] = 0;
    int result = tcp_client_request(server, port, request, buffer, TCP_BUFFER_LENGTH);
    if (result == 0)
    {
        response = buffer;
        #ifdef DEBUG_TCP_REQUEST
        printf("---TCP RESPONSE---\n%s\n^^^\n", response.c_str());
        #endif
    }
    return result;
}
