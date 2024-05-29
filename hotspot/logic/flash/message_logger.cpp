#include "message_logger.h"

MessageLogger::MessageLogger(SYSTEM_INTERFACE_T* systemInterface)
{
	_systemInterface = systemInterface;
}

void MessageLogger::Log(const char* message)
{
}

std::vector<std::string> MessageLogger::GetLogs()
{
	return std::vector<std::string>();
}
