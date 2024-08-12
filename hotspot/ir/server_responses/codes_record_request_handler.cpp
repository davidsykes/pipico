#include "codes_record_request_handler.h"


std::string CodesRecordRequestHandler::HandleRequest(const std::string& request)
{
	return "<form action=\"/record\"><input type = \"submit\" value = \"Record\" /></form>";
}
