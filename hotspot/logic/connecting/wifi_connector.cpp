#include <string.h>
#include "wifi_connector.h"
#include "../common.h"

WiFiConnector::WiFiConnector(SYSTEM_INTERFACE_T* systemInterface)
{
    const char* credentials = (const char* )systemInterface->read_flash_data();
    if (strncmp(credentials, "CRED", 4) == 0)
    {
        loadCredentialsFromString(credentials + 4);
        DEBUG_printf("Found credentials '%s' '%s'", userName.c_str(), password.c_str());
    }
}

void WiFiConnector::loadCredentialsFromString(const char* credentials)
{
    userName = credentials;
    credentials += userName.length() + 1;
    password = credentials;
    credentials += password.length() + 1;
    lastErrorMessage = credentials;
}

bool WiFiConnector::CredentialsAreValid()
{
    return userName.length() > 0;
}
bool WiFiConnector::ConnectToWiFi()
{
    DEBUG_printf("WiFiConnector NOT IMPLEMENTED\n");
    return false;
}
