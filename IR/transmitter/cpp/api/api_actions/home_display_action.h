#pragma once
#include "api_action.h"

class HomeDisplayAction : public ApiAction
{
	ApiAction& codeSequencesDisplayAction;
	ApiAction& logsDisplayAction;

	virtual std::string Action();

public:
	HomeDisplayAction(
		ApiAction& codeSequencesDisplayAction,
		ApiAction& logsDisplayAction)
		: codeSequencesDisplayAction(codeSequencesDisplayAction),
		logsDisplayAction(logsDisplayAction) {}
};
