#include "http_request_router.h"
#include <string.h>

std::string HttpRequestRouter::RouteHttpRequest(const char* request)
{
	if (strncmp(request, "GET / ", 6) == 0)
	{
		return homeRequestHandler.Action();
	}
	if (strncmp(request, "GET /record", 11) == 0)
	{
		return recordRequestHandler.Action();
	}
	if (strncmp(request, "GET /sendcode", 13) == 0)
	{
		return playIrRequestHandler.Action(request + 14);
	}

	return "";
}

