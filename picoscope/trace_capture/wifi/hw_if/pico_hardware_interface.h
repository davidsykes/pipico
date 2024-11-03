#pragma once
#include "ihardware_interface.h"
#include "hardware_interface.h"

class PicoHardwareInterface : public IHardwareInterface
{
    sHardwareInterface* hardware_interface;

    virtual void initialise_pico_stdio(bool wait_for_usb_comms);
    virtual int initialise_wifi_sta(const char* ssid, const char* password);
    virtual void initialise_wifi_ap(const char* ssid, const char* password);

public:
    PicoHardwareInterface();
};
