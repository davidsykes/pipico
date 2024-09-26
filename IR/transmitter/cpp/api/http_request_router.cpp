#include "http_request_router.h"
#include <string.h>

std::string HttpRequestRouter::RouteHttpRequest(const char* request)
{
	if (strncmp(request, "GET / ", 6) == 0)
	{
		return homeRequestHandler.Action();
	}
	if (strncmp(request, "GET /raw ", 9) == 0)
	{
		return rawRequestHandler.Action();
	}
	if (strncmp(request, "GET /sendcode", 13) == 0)
	{
		return playIrRequestHandler.Action(GetSingleToken(request + 14));
	}

	return "";
}

std::string HttpRequestRouter::GetSingleToken(const char* token)
{
	int i = 0;
	while (!isspace(token[i]))
	{
		++i;
	}
	return std::string(token, i);
}