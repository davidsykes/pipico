#pragma once
#include <string>
#include "../flash/flash_hardware.h"

class WiFiConnectionMaker
{
    std::string userName;
    std::string password;

    void loadCredentialsFromString(const char* credentials);

public:
    std::string lastErrorMessage;

    WiFiConnectionMaker(IFlashHardware* flashHardware);
	bool CredentialsAreValid();
    bool ConnectToWiFi();
};