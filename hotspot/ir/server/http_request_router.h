#pragma once
#include "ihttp_request_handler.h"

class HttpRequestRouter : public IHttpRequestHandler
{
    IHttpRequestHandler& homeRequestHandler;

    virtual std::string HandleHttpRequest(const char* request);

public:
    HttpRequestRouter(IHttpRequestHandler& homeHandler) : homeRequestHandler(homeHandler) {}
};