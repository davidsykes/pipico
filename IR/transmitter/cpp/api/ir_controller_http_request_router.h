#pragma once
#include "api_actions/api_action.h"
#include "../wifi/ihttp_request_router.h"

class IrControllerHttpRequestRouter : public IHttpRequestRouter
{
    ApiAction& homeRequestHandler;
    ApiAction& rawRequestHandler;
    ApiAction& playIrRequestHandler;
    ApiAction& playIrSequenceHandler;

    virtual std::string RouteHttpRequest(const char* request);

    std::string GetSingleToken(const char* token);

public:
    IrControllerHttpRequestRouter(ApiAction& homeHandler,
        ApiAction& rawHandler,
        ApiAction& playIrRequestHandler,
        ApiAction& playIrSequenceHandler)
        : homeRequestHandler(homeHandler),
        rawRequestHandler(rawHandler),
        playIrRequestHandler(playIrRequestHandler),
        playIrSequenceHandler(playIrSequenceHandler)
    {}
};