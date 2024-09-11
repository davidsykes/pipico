#pragma once
#include "api_action.h"
#include "../../tools/message_logger.h"

class HomeDisplayAction : public ApiAction
{
	ApiAction& codesDisplayAction;
	ApiAction& logDisplayAction;

	virtual std::string Action();

public:
	HomeDisplayAction(ApiAction& codesDisplayAction,
		ApiAction& logDisplayAction) : codesDisplayAction(codesDisplayAction), logDisplayAction(logDisplayAction) {}
};
