#pragma once
#include <string>
#include <stdlib.h>
#include "tcp_server_implementation.h"

class HotSpotTcpServer
{
    public:
        std::string hotspot_name;
        std::string hotspot_password;

        virtual std::string process_request(const char *request, const char *params) = 0;
};

