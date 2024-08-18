// TODO remove
#include "http_server_home_handler.h"


std::string HttpServerHomeHandler::HandleHttpRequest(const char* request)
{
    printf("IR tcp server reqest\n%s\n^^^\n", request);

    std::string display = codesDisplayRequestHandler.HandleRequest(request);
    printf("Display: %s\n", display.c_str());
    std::string record = codesRecordRequestHandler.HandleRequest(request);
    printf("Record: %s\n", record.c_str());
    return display + "<br><br>" + record;
}
