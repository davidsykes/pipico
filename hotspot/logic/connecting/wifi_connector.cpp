#include "wifi_connector.h"
#include "common.h"

    WifiConnector::WifiConnector(SYSTEM_INTERFACE_T* systemInterface)
    {
        DEBUG_printf("WifiConnector NOT IMPLEMENTED");
    }

	bool WifiConnector::CredentialsAreValid()
    {
        DEBUG_printf("WifiConnector NOT IMPLEMENTED");
        return false;
    }
    bool WifiConnector::ConnectToWifi()
    {
        DEBUG_printf("WifiConnector NOT IMPLEMENTED");
        return false;
    }
    const char* WifiConnector::GetErrorMessage()
    {
        DEBUG_printf("WifiConnector NOT IMPLEMENTED");
        return "WifiConnector not implemented";
    }
    