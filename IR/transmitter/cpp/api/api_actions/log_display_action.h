#pragma once
#include "iapi_action.h"
#include "../../tools/message_logger.h"

class LogDisplayAction : public IApiAction
{
	IMessageLogger& messageLogger;

	virtual std::string ApiAction();

public:
	LogDisplayAction(IMessageLogger& messageLogger) : messageLogger(messageLogger) {}
};
