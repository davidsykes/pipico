#pragma once
#include "../hotspot/logic/tcp_server/tcp_server.h"
#include "server_responses/codes_display_request_handler.h"
#include "server_responses/codes_record_request_handler.h"

class IrRedTcpRequestHandler : public TcpServer
{
    ICodesDisplayRequestHandler& codesDisplayRequestHandler;
    ICodesRecordRequestHandler& codesRecordRequestHandler;

    virtual std::string process_request(const char *request, const char *params);

public:
    IrRedTcpRequestHandler(ICodesDisplayRequestHandler& codesDisplayRequestHandler,
        ICodesRecordRequestHandler& codesRecordRequestHandler)
        : codesDisplayRequestHandler(codesDisplayRequestHandler),
        codesRecordRequestHandler(codesRecordRequestHandler) {}
};

