#pragma once

class WiFiConnector
{
public:
    void ConnectToWiFi(const char* input_form_hotspot_name);
     // TODO Factor this out to a server object
    void ConnectToWiFiTestServer();
};
