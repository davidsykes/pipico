#pragma once
#include <string>
#include <vector>

class IMessageLogger
{
public:
	virtual void Log(const char* message) = 0;
	virtual std::vector<std::string> Logs() = 0;
};

class MessageLogger : public IMessageLogger
{
	std::vector<std::string> logs;

	virtual void Log(const char* message);
	virtual std::vector<std::string> Logs() { return logs;  }
};
