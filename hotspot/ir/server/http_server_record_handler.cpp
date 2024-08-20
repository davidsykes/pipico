#include "http_server_record_handler.h"

std::string HttpServerRecordHandler::ProcessHttpRequest(const char* request)
{
    return picoScopeRecordAndPost.RecordAndPostTrace();
}
