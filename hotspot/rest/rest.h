#pragma once
#include <string>
#include "hardware_interface.hpp"


class RestHandler
{
    IHardwareInterface& hwif;
    std::string server;
    unsigned int port;
    std::string last_request;
    std::string last_response;

public:
    RestHandler(IHardwareInterface& hwif, const char* server, unsigned int port);
    std::string Get(const char*url);
    std::string Put(const char*url, const char* body);
    void Log();
};
