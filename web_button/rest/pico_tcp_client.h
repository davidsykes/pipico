#pragma once
#include "ipico_tcp_client.h"

class PicoTcpClient : public IPicoTcpClient
{
    virtual int tcp_request(const char* server, unsigned int port, const char* request, std::string& response);
};

