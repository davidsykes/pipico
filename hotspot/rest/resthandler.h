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
    std::string last_request;
    std::string last_response;

    virtual std::string Get(const char* url);
    virtual std::string Put(const char* url, const char* body);
    virtual void LogLastRequest();

public:
    RestHandler(IHardwareInterface& hwif, ITcpResponseAnalyser& tcp_analyser, const char* server, unsigned int port);
};
