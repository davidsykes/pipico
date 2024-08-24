#pragma once
#include <string>
#include <pico_hardware_interface.h>
#include "tcp_response_analyser.h"

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
    IHardwareInterface& hw_if;
    ITcpResponseAnalyser& tcpResponseAnalyser;

    virtual int MakeRequest(const std::string& request, std::string& response);

public:
    TcpRequestMaker(
        const std::string& server,
        unsigned int port,
        IHardwareInterface& hw_if,
        ITcpResponseAnalyser& tcpResponseAnalyser) :
        server(server),
        port(port),
        hw_if(hw_if),
        tcpResponseAnalyser(tcpResponseAnalyser){}
};
