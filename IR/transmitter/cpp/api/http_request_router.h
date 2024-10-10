#pragma once
#include "api_actions/api_action.h"
#include "../wifi/ihttp_request_router.h"

class HttpRequestRouter : public IHttpRequestRouter
{
    ApiAction& homeRequestHandler;
    ApiAction& rawRequestHandler;
    ApiAction& playIrRequestHandler;
    ApiAction& playIrSequenceHandler;

    virtual std::string RouteHttpRequest(const char* request);

    std::string GetSingleToken(const char* token);

public:
    HttpRequestRouter(ApiAction& homeHandler,
        ApiAction& rawHandler,
        ApiAction& playIrRequestHandler,
        ApiAction& playIrSequenceHandler)
        : homeRequestHandler(homeHandler),
        rawRequestHandler(rawHandler),
        playIrRequestHandler(playIrRequestHandler),
        playIrSequenceHandler(playIrSequenceHandler)
    {}
};