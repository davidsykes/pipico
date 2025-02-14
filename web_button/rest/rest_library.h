#pragma once
#include "rest_handler.h"
#include "pico_tcp_client.h"

class RestLibrary : public IRestHandler
{
    PicoTcpClient* _pico_tcp_client;
    TcpResponseAnalyser* _tcp_response_analyser;
    TcpRequestErrorLogger* _tcp_request_error_logger;
    TcpRequestMaker* _tcp_request_maker;
    RestHandler* _rest_handler;

    virtual std::string Get(const char* url);
    virtual std::string Put(const char* url, const char* body);
public:
    RestLibrary(const char*ip, int port);
    ~RestLibrary();
};

