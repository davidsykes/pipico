#include "home_display_action.h"

std::string HomeDisplayAction::Action()
{
	return codeSequencesDisplayAction.Action() + logsDisplayAction.Action();
}