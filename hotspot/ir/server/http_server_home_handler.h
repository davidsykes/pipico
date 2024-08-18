#pragma once
#include "ihttp_request_handler.h"
#include "../server_responses/codes_display_request_handler.h"
#include "../server_responses/codes_record_request_handler.h"

class HttpServerHomeHandler : public IHttpRequestHandler
{
     ICodesDisplayRequestHandler& codesDisplayRequestHandler;
     ICodesRecordRequestHandler& codesRecordRequestHandler;


     virtual std::string HandleHttpRequest(const char* request);

 public:
     HttpServerHomeHandler(ICodesDisplayRequestHandler& codesDisplayRequestHandler,
         ICodesRecordRequestHandler& codesRecordRequestHandler)
         : codesDisplayRequestHandler(codesDisplayRequestHandler),
         codesRecordRequestHandler(codesRecordRequestHandler) {}
};


