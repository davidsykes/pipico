#pragma once
#include "../../3rd_party/ihttp_request_router.h"
#include "ihttp_request_handler.h"

class HttpRequestRouter : public IHttpRequestRouter
{
    IHttpRequestHandler& homeRequestHandler;

    virtual int HandleHttpRequest(const char* request, std::string& header, std::string& body);
public:
    HttpRequestRouter(IHttpRequestHandler& homeHandler) : homeRequestHandler(homeHandler) {}
};