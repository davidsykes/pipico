#pragma once
#include "../hotspot/low_level/tcp/tcp_server.h"
#include "server_responses/codes_display_request_handler.h"
#include "server_responses/codes_record_request_handler.h"

class IrTcpRequestHandler : public TcpServer
{
    ICodesDisplayRequestHandler& codesDisplayRequestHandler;
    ICodesRecordRequestHandler& codesRecordRequestHandler;

    virtual std::string process_request(const char *request, const char *params);

public:
    IrTcpRequestHandler(ICodesDisplayRequestHandler& codesDisplayRequestHandler,
        ICodesRecordRequestHandler& codesRecordRequestHandler)
        : codesDisplayRequestHandler(codesDisplayRequestHandler),
        codesRecordRequestHandler(codesRecordRequestHandler) {}
};

