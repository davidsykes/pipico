#include <string.h>
#include "wifi_connection_maker.h"
#include "../common.h"

WiFiConnectionMaker::WiFiConnectionMaker(IFlashHardware* flashHardware)
{
    const char* credentials = (const char* )flashHardware->ReadFlash();
    if (strncmp(credentials, "CRED", 4) == 0)
    {
        loadCredentialsFromString(credentials + 4);
        DEBUG_printf("Found credentials '%s' '%s'\n", userName.c_str(), password.c_str());
    }
}

void WiFiConnectionMaker::loadCredentialsFromString(const char* credentials)
{
    userName = credentials;
    credentials += userName.length() + 1;
    password = credentials;
    credentials += password.length() + 1;
    lastErrorMessage = credentials;
}

bool WiFiConnectionMaker::CredentialsAreValid()
{
    return userName.length() > 0;
}
bool WiFiConnectionMaker::ConnectToWiFi()
{
    DEBUG_printf("WiFiConnectionMaker NOT IMPLEMENTED\n");
    return false;
}
