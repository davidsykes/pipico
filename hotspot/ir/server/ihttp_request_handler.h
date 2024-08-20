#pragma once
#include <string>

class IHttpRequestHandler
{
public:
    virtual std::string ProcessHttpRequest(const char* request) = 0;
};

