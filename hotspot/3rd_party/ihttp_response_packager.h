#pragma once
#include <string>

class IHttpResponsePackager
{
public:
    virtual int RouteRequestAndPackageResponse(const char* request, std::string& header, std::string& body) = 0;
};

