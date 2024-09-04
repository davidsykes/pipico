#pragma once
#include "api_actions/iapi_action.h"

class IHttpRequestRouter
{
public:
    virtual std::string RouteHttpRequest(const char* request) = 0;
};

class HttpRequestRouter : public IHttpRequestRouter
{
    IApiAction& homeRequestHandler;
    IApiAction& recordRequestHandler;

    virtual std::string RouteHttpRequest(const char* request);

public:
    HttpRequestRouter(IApiAction& homeHandler,
        IApiAction& recordHandler)
        : homeRequestHandler(homeHandler),
        recordRequestHandler(recordHandler)
    {}
};