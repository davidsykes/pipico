#pragma once

class WiFiConnector
{
public:
    void ConnectToWiFi(const char* input_form_hotspot_name, const char* password);
    void ConnectToWiFiDirect(const char* ssid, const char* password);
};
