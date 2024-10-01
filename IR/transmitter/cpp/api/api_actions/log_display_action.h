#pragma once
#include "api_action.h"
#include "../../tools/message_logger.h"

class LogDisplayAction : public ApiAction
{
	MessageLogger& messageLogger;

	virtual std::string Action();

public:
	LogDisplayAction(MessageLogger& messageLogger) : messageLogger(messageLogger) {}
};
