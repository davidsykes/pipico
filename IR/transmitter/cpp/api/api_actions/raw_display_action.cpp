#include "raw_display_action.h"

std::string RawDisplayAction::Action()
{
	return codesDisplayAction.Action() +
		"<br>" +
		logDisplayAction.Action();
}