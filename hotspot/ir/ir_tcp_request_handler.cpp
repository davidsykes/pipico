#include "ir_tcp_request_handler.h"

std::string IrTcpRequestHandler::process_request(const char *request, const char *params)
{
    printf("tcp server reqest %s", request);

    return codesDisplayRequestHandler.HandleRequest(request) +
        codesRecordRequestHandler.HandleRequest(request);
}