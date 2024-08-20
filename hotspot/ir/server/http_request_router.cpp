#include "http_request_router.h"
#include <string.h>

std::string HttpRequestRouter::HandleHttpRequest(const char* request)
{
	if (strncmp(request, "/ ", 2) == 0)
	{
		return homeRequestHandler.HandleHttpRequest(request);
	}

	return "";
}

