#pragma once
#include "record_ir_action.h"

class RecordIrAction : public IApiAction
{
	IMessageLogger& messageLogger;

	virtual std::string ApiAction();

public:
	LogDisplayAction(IMessageLogger& messageLogger) : messageLogger(messageLogger) {}
};
