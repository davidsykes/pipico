

// Code copied from pipico/libraries.hw_if



#include "pico_hardware_interface.h"

#define TCP_BUFFER_LENGTH   2048
//#define DEBUG_TCP_REQUEST


PicoHardwareInterface::PicoHardwareInterface()
{
    hardware_interface = create_hardware_interface();
    hardware_interface->cyw43_arch_init();
}

void PicoHardwareInterface::initialise_pico_stdio(bool wait_for_usb_comms)
{
    hardware_interface->initialise_pico_stdio(wait_for_usb_comms);
}

int PicoHardwareInterface::initialise_wifi_sta(const char* ssid, const char* password)
{
    return hardware_interface->initialise_wifi_sta(ssid, password);
}

void PicoHardwareInterface::initialise_wifi_ap(const char* ssid, const char* password)
{
    hardware_interface->initialise_wifi_ap(ssid, password);
}

uint64_t PicoHardwareInterface::get_time_us()
{
    return hardware_interface->get_time_us();
}

void PicoHardwareInterface::initialise_input_pin(int pin_number)
{
    hardware_interface->initialise_input_pin(pin_number);
}

void PicoHardwareInterface::gpio_set_pull_up(int pin_number, int value)
{
    hardware_interface->gpio_set_pull_up(pin_number, value);
}

void PicoHardwareInterface::initialise_output_pin(int pin_number)
{
    hardware_interface->initialise_output_pin(pin_number);
}

int PicoHardwareInterface::gpio_get(int pin_number)
{
    return hardware_interface->gpio_get(pin_number);
}

int PicoHardwareInterface::get_pins()
{
    return hardware_interface->get_pins();
}

int PicoHardwareInterface::wait_pins_change(sPinsChangeData* pinsChangeData, int mask, uint64_t timeout)
{
    return hardware_interface->wait_pins_change(pinsChangeData, mask, timeout);
}

void PicoHardwareInterface::gpio_put(int pin_number, bool value)
{
    hardware_interface->gpio_put(pin_number, value);
}

uint64_t PicoHardwareInterface::gpio_put_at_us(int pin_number, bool value, uint64_t time_us)
{
    return hardware_interface->gpio_put_at_us(pin_number, value, time_us);
}

void PicoHardwareInterface::set_led(bool value)
{
    hardware_interface->set_led(value);
}

void PicoHardwareInterface::sleep_us(int useconds)
{
    hardware_interface->sleep_us(useconds);
}

int PicoHardwareInterface::tcp_request(const char* server, unsigned int port, const char* request, std::string& response)
{
    #ifdef DEBUG_TCP_REQUEST
    printf("---TCP REQUEST---\n%s\n^^^\n", request);
    #endif
    char buffer[TCP_BUFFER_LENGTH];
    buffer[0] = 0;
    int result = hardware_interface->tcp_request(server, port, request, buffer, TCP_BUFFER_LENGTH);
    if (result == 0)
    {
        response = buffer;
        #ifdef DEBUG_TCP_REQUEST
        printf("---TCP RESPONSE---\n%s\n^^^\n", response.c_str());
        #endif
    }
    return result;
}

void PicoHardwareInterface::cyw43_arch_deinit()
{
    hardware_interface->cyw43_arch_deinit();
}