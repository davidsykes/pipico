#pragma once
#include "ihttp_request_router.h"

class HotSpotRequestRouter : public IHttpRequestRouter
{
    IHttpRequestRouter& ssidInputForm;

    virtual std::string RouteHttpRequest(const char* request);

public:
    HotSpotRequestRouter(IHttpRequestRouter& ssidInputForm)
        : ssidInputForm(ssidInputForm) {}
};