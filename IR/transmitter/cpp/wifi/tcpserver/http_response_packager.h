#pragma once
#include <string>
#include "../api/http_request_router.h"

class IHttpResponsePackager
{
public:
    virtual int RouteRequestAndPackageResponse(const char* request, std::string& header, std::string& body) = 0;
};


class HttpResponsePackager : public IHttpResponsePackager
{
    IHttpRequestRouter& requestRouter;

public:
    HttpResponsePackager(IHttpRequestRouter& requestRouter) :requestRouter(requestRouter) {}

    virtual int RouteRequestAndPackageResponse(const char* request, std::string& header, std::string& body);
};

