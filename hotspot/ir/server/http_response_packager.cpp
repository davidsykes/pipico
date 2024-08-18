#include "http_response_packager.h"

const std::string header1 = "HTTP/1.1 200 OK\r\nContent-Length: ";
const std::string header2 = "\r\nContent-Type : text/plain; charset=utf-8";

int HttpResponsePackager::RouteRequestAndPackageResponse(const char* request, std::string& header, std::string& body)
{
	body = requestRouter.HandleHttpRequest(request);

	if (body.length() > 0)
	{
		header = header1 + std::to_string(body.length()) + header2;
		return 1;
	}
	return 0;
}



