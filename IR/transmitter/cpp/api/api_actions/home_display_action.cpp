#include "home_display_action.h"

std::string HomeDisplayAction::ApiAction()
{
	return codesDisplayAction.ApiAction() +
		"<br>" +
		logDisplayAction.ApiAction();
}