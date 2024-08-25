#pragma once

class ITcpRequestErrorLogger
{
public:
    virtual void LogError(const std::string& request, const std::string& response) = 0;
};
