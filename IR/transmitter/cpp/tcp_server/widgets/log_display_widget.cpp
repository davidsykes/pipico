#include "log_display_widget.h"
#include <sstream>



std::string LogDisplayWidget::RenderWidget()
{
	auto logs = messageLogger.Logs();
	std::ostringstream str;

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