#include "ir_tcp_request_handler.h"

std::string IrTcpRequestHandler::process_request(const char *request, const char *params)
{
    printf("IR tcp server reqest\n%s\n^^^\n", request);

    std::string display = codesDisplayRequestHandler.HandleRequest(request);
    printf("Display: %s\n", display.c_str());
    std::string record = codesRecordRequestHandler.HandleRequest(request);
    printf("Record: %s\n", record.c_str());
    return display + "<br><br>" + record;
}