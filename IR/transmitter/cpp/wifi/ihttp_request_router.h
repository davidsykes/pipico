#pragma once

class IHttpRequestRouter
{
public:
    virtual std::string RouteHttpRequest(const char* request) = 0;
};
