#pragma once
#include "system_interface.h"

class WifiConnector
{
public:
    WifiConnector(SYSTEM_INTERFACE_T* systemInterface);
	bool CredentialsAreValid();
    bool ConnectToWifi();
    const char* GetErrorMessage();
};