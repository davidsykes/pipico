#pragma once
#include <string>
#include "ipico_tcp_client.h"
#include "tcp_response_analyser.h"
#include "tcp_request_error_logger.h"

class ITcpRequestMaker
{
public:
    virtual int MakeRequest(const std::string& request, std::string& response) = 0;
    virtual ~ITcpRequestMaker() {}
};


class TcpRequestMaker : public ITcpRequestMaker
{
    std::string server;
    unsigned int port;
    IPicoTcpClient& pico_tcp_client;
    ITcpResponseAnalyser& tcpResponseAnalyser;
    ITcpRequestErrorLogger& tcpRequestErrorLogger;

    virtual int MakeRequest(const std::string& request, std::string& response);

    int ExtractStatusAndBody(const std::string& server_response, std::string& response);
    int MakeServerErrorResponse(int tcp_request_result, std::string& response);
public:
    TcpRequestMaker(
        const std::string& server,
        unsigned int port,
        IPicoTcpClient& pico_tcp_client,
        ITcpResponseAnalyser& tcpResponseAnalyser,
        ITcpRequestErrorLogger& tcpRequestErrorLogger) :
        server(server),
        port(port),
        pico_tcp_client(pico_tcp_client),
        tcpResponseAnalyser(tcpResponseAnalyser),
        tcpRequestErrorLogger(tcpRequestErrorLogger){}
};
