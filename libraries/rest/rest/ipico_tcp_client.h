#pragma once
#include <string>

class IPicoTcpClient
{
public:
    virtual int tcp_request(const char* server, unsigned int port, const char* request, std::string& response)=0;
};

