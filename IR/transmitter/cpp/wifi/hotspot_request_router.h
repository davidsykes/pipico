#pragma once
#include "ihttp_request_router.h"
#include "input_form/irenderer.h"

class HotSpotRequestRouter : public IHttpRequestRouter
{
    IRenderer& ssidInputForm;

    virtual std::string RouteHttpRequest(const char* request);

public:
    HotSpotRequestRouter(IRenderer& ssidInputForm)
        : ssidInputForm(ssidInputForm) {}
};