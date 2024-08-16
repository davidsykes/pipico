#pragma once
#include <string>

class IHttpRequestRouter
{
public:
    virtual int HandleHttpRequest(const char* request, std::string& header, std::string& body) = 0;
};

