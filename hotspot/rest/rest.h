#pragma once
#include <string>
#include "hardware_interface.hpp"
#include "response_processor.h"


class RestHandler
{
    IHardwareInterface& hwif;
    std::string server;
    unsigned int port;
    ResponseProcessor& responseProcessor;

public:
    RestHandler(IHardwareInterface& hwif, const char* server, unsigned int port, ResponseProcessor& responseProcessor);
    std::string Get(const char*url);
    std::string Put(const char*url, const char* body);
};
