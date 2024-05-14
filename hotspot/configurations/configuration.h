#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#include <string>

class Configuration
{
    public:
        std::string hotspot_name;
        std::string hotspot_password;

        virtual std::string process_request(const char *request, const char *params) = 0;
};

#endif
