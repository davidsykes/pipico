#pragma once
#include "hw_if/pico_hardware_interface.h"
#include "low_level/tcp/tcp_server.h"

class WiFiConnector
{
public:
    void ConnectToWiFi(const char* input_form_hotspot_name);
    void ConnectToWiFiDirect(IHardwareInterface& hw_if, const char* ssid, const char* password);
     // TODO Factor this out to a server object
    void ConnectToWiFiTestServer(TcpServer& tcp_server);
};
