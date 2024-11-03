#include "pico_hardware_interface.h"

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
