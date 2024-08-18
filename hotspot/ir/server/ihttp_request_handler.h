#pragma once
#include <string>

class IHttpRequestHandler
{
public:
    virtual std::string HandleHttpRequest(const char* request) = 0;
};

