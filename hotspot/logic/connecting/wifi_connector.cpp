#include "wifi_connector.h"
#include "common.h"

    WiFiConnector::WiFiConnector(SYSTEM_INTERFACE_T* systemInterface)
    {
        DEBUG_printf("WiFiConnector NOT IMPLEMENTED");
    }

	bool WiFiConnector::CredentialsAreValid()
    {
        DEBUG_printf("WiFiConnector NOT IMPLEMENTED");
        return false;
    }
    bool WiFiConnector::ConnectToWiFi()
    {
        DEBUG_printf("WiFiConnector NOT IMPLEMENTED");
        return false;
    }
    const char* WiFiConnector::GetErrorMessage()
    {
        DEBUG_printf("WiFiConnector NOT IMPLEMENTED");
        return "WiFiConnector not implemented";
    }
    