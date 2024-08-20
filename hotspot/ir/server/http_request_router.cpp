#include "http_request_router.h"
#include <string.h>

std::string HttpRequestRouter::RouteHttpRequest(const char* request)
{
	if (strncmp(request, "GET / ", 6) == 0)
	{
		return homeRequestHandler.ProcessHttpRequest(request);
	}
	if (strncmp(request, "GET /record", 11) == 0)
	{
		return recordequestHandler.ProcessHttpRequest(request);
	}

	return "";
}

