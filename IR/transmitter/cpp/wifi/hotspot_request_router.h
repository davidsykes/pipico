#pragma once
#include "ihttp_request_router.h"

class HotSpotRequestRouter : public IHttpRequestRouter
{
    virtual std::string RouteHttpRequest(const char* request) { return "hello world"; }
};