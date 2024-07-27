#pragma once
#include <string>
#include "iresthandler.h"
#include "hardware_interface.hpp"
#include "itcpresponseanalyser.h"

class RestHandler : public IRestHandler
{
    IHardwareInterface& hwif;
    ITcpResponseAnalyser& tcp_analyser;
    std::string server;
    unsigned int port;

    std::string MakeRequest(const char* url, const char* body);
    std::string PutRaw(const std::string& request);
    void LogLastRequest(const std::string& request, const std::string& response);

    virtual std::string Get(const char* url);
    virtual std::string Put(const char* url, const char* body);

public:
    RestHandler(IHardwareInterface& hwif, ITcpResponseAnalyser& tcp_analyser, const char* server, unsigned int port);
};
