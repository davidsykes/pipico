#pragma once
#include "api_actions/api_action.h"

class IHttpRequestRouter
{
public:
    virtual std::string RouteHttpRequest(const char* request) = 0;
};

class HttpRequestRouter : public IHttpRequestRouter
{
    ApiAction& homeRequestHandler;
    ApiAction& playIrRequestHandler;

    virtual std::string RouteHttpRequest(const char* request);

    std::string GetSingleToken(const char* token);

public:
    HttpRequestRouter(ApiAction& homeHandler,
        ApiAction& playIrRequestHandler)
        : homeRequestHandler(homeHandler),
        playIrRequestHandler(playIrRequestHandler)
    {}
};