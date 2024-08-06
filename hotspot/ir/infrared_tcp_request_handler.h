#pragma once
#include "../hotspot/logic/tcp_server/tcp_server.h"

class InfraRedTcpRequestHandler : public TcpServer
{
    virtual std::string process_request(const char *request, const char *params);
};

