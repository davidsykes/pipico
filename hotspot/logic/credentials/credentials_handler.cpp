#include "credentials_handler.h"

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
    size_t begin = credentials.find(SSID_PREFIX);
    size_t separator = credentials.find('&');
    if (begin == 0 &&
        separator > 0)
    {
        std::string unconvertedSSID = credentials.substr(SSID_PREFIX_LEN, separator - SSID_PREFIX_LEN);

        std::string p2 = credentials.substr(separator + 1);
        size_t pword = credentials.find(PASSWORD_PREFIX, separator);
        if (pword == 0)
        {
            std::string unconvertedPassword = p2.substr(PASSWORD_PREFIX_LEN);
            ConvertAndWriteCredentials(unconvertedSSID, unconvertedPassword);
        }
    }
}

void CredentialsHandler::ConvertAndWriteCredentials(const std::string& SSID, const std::string& password)
{
    WriteCredentials(_percentDecoder->Decode(SSID), _percentDecoder->Decode(password));
}

void CredentialsHandler::WriteCredentials(const std::string& SSID, const std::string& password)
{
    _flashManager->WriteToFlash(SSID, password);
}