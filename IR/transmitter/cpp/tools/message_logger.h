#pragma once
#include <string>
#include <vector>

class IMessageLogger
{
public:
	virtual void Log(const std::string&  message) = 0;
};

class MessageLogger : public IMessageLogger
{
	std::vector<std::string> logs;

	virtual void Log(const std::string& message);
public:
	std::vector<std::string> Logs() { return logs;  }
};
