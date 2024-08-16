#include "http_request_router.h"

int HttpRequestRouter::HandleHttpRequest(const char* request, std::string& header, std::string& body)
{
	if (strncmp(request, "/ ", 2) == 0)
	{
		return homeRequestHandler.HandleHttpRequest(request, header, body);
	}

	return 0;
}

