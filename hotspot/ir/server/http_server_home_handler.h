#pragma once
#include "../../3rd_party/ihttp_request_router.h"
#include "../server_responses/codes_display_request_handler.h"
#include "../server_responses/codes_record_request_handler.h"

class HttpServerHomeHandler : public IHttpRequestRouter
{
     ICodesDisplayRequestHandler& codesDisplayRequestHandler;
     ICodesRecordRequestHandler& codesRecordRequestHandler;

     virtual int HandleHttpRequest(const char* request, std::string& header, std::string& body);
//     virtual std::string process_request(const char *request, const char *params);

 public:
     HttpServerHomeHandler(ICodesDisplayRequestHandler& codesDisplayRequestHandler,
         ICodesRecordRequestHandler& codesRecordRequestHandler)
         : codesDisplayRequestHandler(codesDisplayRequestHandler),
         codesRecordRequestHandler(codesRecordRequestHandler) {}
};


