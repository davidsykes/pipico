#include "http_server_home_handler.h"

std::string HttpServerHomeHandler::ProcessHttpRequest(const char* request)
{
    std::string display = codesDisplayRequestHandler.HandleRequest(request);
    std::string record = codesRecordRequestHandler.HandleRequest(request);
    return display + "<br><br>" + record;
}
