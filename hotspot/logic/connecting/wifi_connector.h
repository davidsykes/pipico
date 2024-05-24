#pragma once
#include "system_interface.h"

class WiFiConnector
{
public:
    WiFiConnector(SYSTEM_INTERFACE_T* systemInterface);
	bool CredentialsAreValid();
    bool ConnectToWiFi();
    const char* GetErrorMessage();
};