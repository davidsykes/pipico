#include <vector>
#include <string>
#include "system_interface.h"


class IMessageLogger
{
public:
	virtual void Log(const char* message) = 0;
	virtual std::vector<std::string> GetLogs() = 0;
};

class MessageLogger : public IMessageLogger
{
	SYSTEM_INTERFACE_T* _systemInterface;

	virtual void Log(const char* message);
	virtual std::vector<std::string> GetLogs();
public:
	MessageLogger(SYSTEM_INTERFACE_T* systemInterface);
};