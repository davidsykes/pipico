#include "message_logger.h"


void MessageLogger::Log(const std::string& message)
{
	logs.push_back(message);
}
