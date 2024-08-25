#pragma once

class ITcpRequestErrorLogger
{
public:
    virtual void LogError(const std::string& request, const std::string& response) = 0;
};


class TcpRequestErrorLogger : public ITcpRequestErrorLogger
{
    virtual void LogError(const std::string& request, const std::string& response)
    {
        printf("TcpRequestErrorLogger NOT IMPLEMENTED\r\n");
    }
};
