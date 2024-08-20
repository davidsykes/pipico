#pragma once
#include "ihttp_request_handler.h"
#include "../pico_scope/pico_scope_record_and_post.h"

class HttpServerRecordHandler : public IHttpRequestHandler
{
    IPicoScopeRecordAndPost& picoScopeRecordAndPost;

     virtual std::string ProcessHttpRequest(const char* request);

 public:
     HttpServerRecordHandler(IPicoScopeRecordAndPost& rap)
         : picoScopeRecordAndPost(rap) {}
};


