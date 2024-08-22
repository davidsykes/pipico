#pragma once
#include "../ihttp_request_handler.h"
#include "../../server_responses/codes_display_request_handler.h"
#include "../../server_responses/codes_record_request_handler.h"

class HttpServerHomePage : public IHttpRequestHandler
{
     ICodesDisplayRequestHandler& codesDisplayRequestHandler;
     ICodesRecordRequestHandler& codesRecordRequestHandler;


     virtual std::string ProcessHttpRequest(const char* request);

 public:
     HttpServerHomePage(ICodesDisplayRequestHandler& codesDisplayRequestHandler,
         ICodesRecordRequestHandler& codesRecordRequestHandler)
         : codesDisplayRequestHandler(codesDisplayRequestHandler),
         codesRecordRequestHandler(codesRecordRequestHandler) {}
};


