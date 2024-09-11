#include "home_display_action.h"

std::string HomeDisplayAction::Action()
{
	return codesDisplayAction.Action() +
		"<br>" +
		logDisplayAction.Action();
}