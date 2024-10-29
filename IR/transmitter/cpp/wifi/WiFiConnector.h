#pragma once
#include "../hw_if/pico_hardware_interface.h"

class WiFiConnector
{
public:
    void ConnectToWiFi(IHardwareInterface& hw_if, const char* input_form_hotspot_name, const char* password);
    void ConnectToWiFiDirect(IHardwareInterface& hw_if, const char* ssid, const char* password);
};
