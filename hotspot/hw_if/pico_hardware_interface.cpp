#include "pico_hardware_interface.h"

#define TCP_BUFFER_LENGTH   2048

PicoHardwareInterface::PicoHardwareInterface()
{
    hardware_interface = create_hardware_interface();
    hardware_interface->cyw43_arch_init();
}

void PicoHardwareInterface::initialise_pico_stdio()
{
    hardware_interface->initialise_pico_stdio();
}

int PicoHardwareInterface::initialise_wifi(const char* ssid, const char* password)
{
    return hardware_interface->initialise_wifi(ssid, password);
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
    printf("---TCP REQUEST---\n%s\n^^^\n", request);
    char buffer[TCP_BUFFER_LENGTH];
    buffer[0] = 0;
    int result = hardware_interface->tcp_request(server, port, request, buffer, TCP_BUFFER_LENGTH);
    if (result == 0)
    {
        response = buffer;
        printf("---TCP RESPONSE---\n%s\n^^^\n", response.c_str());
    }
    return result;
}

void PicoHardwareInterface::cyw43_arch_deinit()
{
    hardware_interface->cyw43_arch_deinit();
}