#include "message_logger.h"


void MessageLogger::Log(const char* message)
{
	logs.push_back(message);
}
