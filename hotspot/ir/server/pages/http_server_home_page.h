#pragma once
#include "../ihttp_request_handler.h"
#include "../../server_responses/codes_display_request_handler.h"
#include "../../server_responses/codes_record_request_handler.h"
#include "../widgets/iwidget.h"

class HttpServerHomePage : public IHttpRequestHandler
{
     ICodesDisplayRequestHandler& codesDisplayRequestHandler;
     ICodesRecordRequestHandler& codesRecordRequestHandler;
     IWidget& logsDisplayWidget;

     virtual std::string ProcessHttpRequest(const char* request);

 public:
     HttpServerHomePage(ICodesDisplayRequestHandler& codesDisplayRequestHandler,
         ICodesRecordRequestHandler& codesRecordRequestHandler,
         IWidget& logsDisplayWidget)
         : codesDisplayRequestHandler(codesDisplayRequestHandler),
         codesRecordRequestHandler(codesRecordRequestHandler),
         logsDisplayWidget(logsDisplayWidget) {}
};


