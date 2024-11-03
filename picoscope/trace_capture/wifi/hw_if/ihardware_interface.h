#pragma once

class IHardwareInterface
{
public:
    virtual void initialise_pico_stdio(bool wait_for_usb_comms)=0;
    virtual int initialise_wifi_sta(const char* ssid, const char* password)=0;
    virtual void initialise_wifi_ap(const char* ssid, const char* password)=0;
};

