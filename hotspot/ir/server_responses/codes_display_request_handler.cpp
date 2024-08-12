#include "codes_display_request_handler.h"


std::string CodesDisplayRequestHandler::HandleRequest(const std::string& request)
{
	return "<form action=\"/display\"><input type = \"submit\" value = \"Display\" /></form>";
}
