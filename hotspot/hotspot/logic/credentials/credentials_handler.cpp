#include "credentials_handler.h"
#include <memory.h>

constexpr auto SSID_PREFIX = "ssid=";
constexpr auto SSID_PREFIX_LEN = 5;
constexpr auto PASSWORD_PREFIX = "password=";
constexpr auto PASSWORD_PREFIX_LEN = 9;

CredentialsHandler::CredentialsHandler(IPercentDecoder* percentDecoder, IFlashManager* flashManager)
{
    _percentDecoder = percentDecoder;
    _flashManager = flashManager;
}

void CredentialsHandler::HandleCredentials(std::string credentials)
{
    if (strncmp(credentials.c_str(), SSID_PREFIX, SSID_PREFIX_LEN) != 0)
    {
        SetError("SSID not found.");
        return;
    }

    size_t ampersand = credentials.find('&');
    if (ampersand == std::string::npos)
    {
        SetError("Password not found.");
        return;
    }
    std::string unconvertedSSID = credentials.substr(SSID_PREFIX_LEN, ampersand - SSID_PREFIX_LEN);

    if (strncmp(credentials.c_str() + ampersand + 1, PASSWORD_PREFIX, PASSWORD_PREFIX_LEN) != 0)
    {
        SetError("Password not found.");
        return;
    }

    std::string unconvertedPassword = credentials.substr(ampersand + 1 + PASSWORD_PREFIX_LEN);

    ConvertAndWriteCredentials(unconvertedSSID, unconvertedPassword);
}

void CredentialsHandler::ConvertAndWriteCredentials(const std::string& SSID, const std::string& password)
{
    WriteCredentials(_percentDecoder->Decode(SSID), _percentDecoder->Decode(password));
}

void CredentialsHandler::WriteCredentials(const std::string& SSID, const std::string& password)
{
    _flashManager->WriteToFlash(SSID, password, "");
}

void CredentialsHandler::SetError(const std::string& error)
{
    _flashManager->WriteToFlash("", "", error);
}