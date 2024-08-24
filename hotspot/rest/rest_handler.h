#pragma once
#include <string>
#include "pico_hardware_interface.h"
#include "tcp_response_analyser.h"


class IRestHandler
{
public:
    virtual std::string Get(const char* url) = 0;
    virtual std::string Put(const char* url, const char* body) = 0;
};

class RestHandler : public IRestHandler
{
    IHardwareInterface& hwif;
    ITcpResponseAnalyser& tcp_analyser;
    std::string server;
    unsigned int port;

    std::string MakeRequest(const char* url, const char* body);
    std::string PutRaw2(const std::string& request);
    void LogLastRequest(const std::string& request, const std::string& response);

    virtual std::string Get(const char* url);
    virtual std::string Put(const char* url, const char* body);

public:
    RestHandler(IHardwareInterface& hwif, ITcpResponseAnalyser& tcp_analyser, const char* server, unsigned int port);
};
