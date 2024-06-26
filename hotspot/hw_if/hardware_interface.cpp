#include "hardware_interface.hpp"

PicoHardwareInterface::PicoHardwareInterface()
{
    hardware_interface = create_hardware_interface();
    hardware_interface->cyw43_arch_init();
}

void PicoHardwareInterface::initialise_pico_stdio()
{
    hardware_interface->initialise_pico_stdio();
}

uint64_t PicoHardwareInterface::get_time_us()
{
    return hardware_interface->get_time_us();
}

void PicoHardwareInterface::initialise_input_pin(int pin_number)
{
    hardware_interface->initialise_input_pin(pin_number);
}

void PicoHardwareInterface::initialise_output_pin(int pin_number)
{
    hardware_interface->initialise_output_pin(pin_number);
}

int PicoHardwareInterface::gpio_get(int pin_number)
{
    return hardware_interface->gpio_get(pin_number);
}

uint64_t PicoHardwareInterface::wait_value(int pin_number, int value, uint64_t timeout)
{
    return hardware_interface->wait_value(pin_number, value, timeout);
}

void PicoHardwareInterface::gpio_put(int pin_number, int value)
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