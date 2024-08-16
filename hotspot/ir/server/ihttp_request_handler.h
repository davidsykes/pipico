#pragma once

class IHttpRequestHandler
{
public:
    virtual int HandleHttpRequest(const char* request, std::string& header, std::string& body) = 0;
};

