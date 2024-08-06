#pragma once
#include <string>

class TcpServer
{
    public:
        std::string hotspot_name;
        std::string hotspot_password;

        virtual std::string process_request(const char *request, const char *params) = 0;
};


