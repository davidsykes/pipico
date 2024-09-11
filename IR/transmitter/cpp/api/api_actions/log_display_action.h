#pragma once
#include "api_action.h"
#include "../../tools/message_logger.h"

class LogDisplayAction : public ApiAction
{
	IMessageLogger& messageLogger;

	virtual std::string Action();

public:
	LogDisplayAction(IMessageLogger& messageLogger) : messageLogger(messageLogger) {}
};
