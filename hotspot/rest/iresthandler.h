#pragma once
#include <string>

class IRestHandler
{
public:
    virtual std::string Get(const char* url) = 0;
    virtual std::string Put(const char* url, const char* body) = 0;
    virtual void LogLastRequest() = 0;
};
