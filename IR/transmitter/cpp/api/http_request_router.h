#pragma once
#include "ihttp_request_router.h"
#include "ihttp_request_handler.h"

class HttpRequestRouter : public IHttpRequestRouter
{
    IHttpRequestHandler& homeRequestHandler;
    IHttpRequestHandler& recordRequestHandler;

    virtual std::string RouteHttpRequest(const char* request);

public:
    HttpRequestRouter(IHttpRequestHandler& homeHandler,
        IHttpRequestHandler& recordHandler)
        : homeRequestHandler(homeHandler),
        recordRequestHandler(recordHandler)
    {}
};