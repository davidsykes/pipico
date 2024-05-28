#pragma once
#include <string>
#include "../../interface/system_interface.h"

class WiFiConnector
{
    std::string userName;
    std::string password;

    void loadCredentialsFromString(const char* credentials);

public:
    std::string lastErrorMessage;

    WiFiConnector(SYSTEM_INTERFACE_T* systemInterface);
	bool CredentialsAreValid();
    bool ConnectToWiFi();
};