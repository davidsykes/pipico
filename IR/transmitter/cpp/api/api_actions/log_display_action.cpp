#include "log_display_action.h"
#include <sstream>



std::string LogDisplayAction::Action()
{
	auto logs = messageLogger.Logs();
	if (logs.size() == 0)
	{
		return "";
	}

	std::ostringstream str;

	str << "<br><br>There are " << logs.size() << " logs<br>\n";

	for (int i = 0; i < logs.size(); ++i)
	{
		if (i > 0)
		{
			str << "<br>";
		}
		str << logs[i];
	}

	return str.str();
}