#pragma once
#include <string>
#include "../hotspot/flash_hardware.h"

class WiFiConnector
{
    std::string userName;
    std::string password;

    void loadCredentialsFromString(const char* credentials);

public:
    std::string lastErrorMessage;

    WiFiConnector(IFlashHardware* flashHardware);
	bool CredentialsAreValid();
    bool ConnectToWiFi();
};