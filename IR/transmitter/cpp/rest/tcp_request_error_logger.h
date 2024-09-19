#pragma once

class ITcpRequestErrorLogger
{
public:
    virtual void LogError(int tcp_request_result, const std::string& server, int port, const std::string& request, const std::string& response) = 0;
};

class TcpRequestErrorLogger : public ITcpRequestErrorLogger
{
    virtual void LogError(int tcp_request_result, const std::string& server, int port, const std::string& request, const std::string& response)
    {
        printf("\nTCP REQUEST ERROR %d\n%s:%d\n%s\n+-+-+-+-+-+-+-+-+-+-+\n%s\n^^^^^^^^^^^^^^^^\n",
            tcp_request_result,
            server.c_str(),
            port,
            request.c_str(),
            response.c_str());
    }
};
