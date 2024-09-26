#pragma once
#include "api_action.h"
#include "../../tools/message_logger.h"

class RawDisplayAction : public ApiAction
{
	ApiAction& codesDisplayAction;
	ApiAction& logDisplayAction;

	virtual std::string Action();

public:
	RawDisplayAction(ApiAction& codesDisplayAction,
		ApiAction& logDisplayAction) : codesDisplayAction(codesDisplayAction), logDisplayAction(logDisplayAction) {}
};
