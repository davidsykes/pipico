#pragma once
#include <string>
#include "tcp_request_maker.h"


class IRestHandler
{
public:
    virtual std::string Get(const char* url) = 0;
    virtual std::string Put(const char* url, const char* body) = 0;
};

class RestHandler : public IRestHandler
{
    ITcpRequestMaker& tcpRequestMaker;

    std::string MakeRequest(const char* url, const char* body);

    virtual std::string Get(const char* url);
    virtual std::string Put(const char* url, const char* body);

public:
    RestHandler(ITcpRequestMaker& tcpRequestMaker) :
        tcpRequestMaker(tcpRequestMaker) {}
};
