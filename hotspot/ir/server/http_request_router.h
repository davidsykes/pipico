#pragma once
#include "../../3rd_party/ihttp_request_router.h"

class HttpRequestRouter : public IHttpRequestRouter
{
    IHttpRequestRouter& homeRequestHandler;

    virtual int HandleHttpRequest(const char* request, std::string& header, std::string& body);
public:
    HttpRequestRouter(IHttpRequestRouter& homeHandler) : homeRequestHandler(homeHandler) {}
};