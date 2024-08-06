#include "infrared_tcp_request_handler.h"

std::string InfraRedTcpRequestHandler::process_request(const char *request, const char *params)
{
    printf("tcp server reqest %s", request);

    return "bioo";
}