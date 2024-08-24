#pragma once
#include <string>
#include <pico_hardware_interface.h>

class ITcpRequestMaker
{
public:
    virtual int MakeRequest(const std::string& request) = 0;
    virtual ~ITcpRequestMaker() {}
};


class TcpRequestMaker : public ITcpRequestMaker
{
    std::string server;
    unsigned int port;
    IHardwareInterface& hw_if;

    virtual int MakeRequest(const std::string& request);

public:
    TcpRequestMaker(const std::string& server, unsigned int port, IHardwareInterface& hw_if) :
        server(server),
        port(port),
        hw_if(hw_if) {}
};
