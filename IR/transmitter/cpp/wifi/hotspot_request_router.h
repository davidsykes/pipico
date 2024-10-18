#pragma once
#include "ihttp_request_router.h"
#include "input_form/irenderer.h"

class HotSpotRequestRouter : public IHttpRequestRouter
{
    IRenderer& ssidInputForm;
    IRenderer& hotspotsubmit;

    virtual std::string RouteHttpRequest(const char* request);

public:
    HotSpotRequestRouter(IRenderer& ssidInputForm, IRenderer& hotspotsubmit)
        : ssidInputForm(ssidInputForm), hotspotsubmit(hotspotsubmit) {}
};