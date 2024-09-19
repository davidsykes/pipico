#pragma once

class ITcpRequestErrorLogger
{
public:
    virtual void LogError(int tcp_request_result, const std::string& request, const std::string& response) = 0;
};


class TcpRequestErrorLogger : public ITcpRequestErrorLogger
{
    virtual void LogError(int tcp_request_result, const std::string& request, const std::string& response)
    {
        printf("\nTCP REQUEST ERROR %d\n%s\n+-+-+-+-+-+-+-+-+-+-+\n%s\n^^^^^^^^^^^^^^^^\n", tcp_request_result, request.c_str(), response.c_str());
    }
};
