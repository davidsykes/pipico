#pragma once
#include "configuration.h"

class LedConfiguration : public Configuration
{
    public:
        LedConfiguration();
        virtual std::string process_request(const char *request, const char *params);
};

