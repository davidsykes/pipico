#pragma once
#include "iapi_action.h"
#include "../../tools/message_logger.h"

class HomeDisplayAction : public IApiAction
{
	IApiAction& codesDisplayAction;
	IApiAction& logDisplayAction;

	virtual std::string ApiAction();

public:
	HomeDisplayAction(IApiAction& codesDisplayAction,
		IApiAction& logDisplayAction) : codesDisplayAction(codesDisplayAction), logDisplayAction(logDisplayAction) {}
};
