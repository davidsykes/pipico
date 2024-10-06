#include "http_response_packager.h"

const std::string header1 = "HTTP/1.1 200 OK\r\nContent-Length: ";
const std::string header2 = "\r\nContent-Type : text/html; charset=utf-8\r\nConnection: close\r\n\r\n";
const std::string body_head = "<!DOCTYPE html><html><head><style type=\"text/css\">button{width: 40%;height:10 %;}</style></head><body>";
const std::string body_foot = "</body></html> ";

int HttpResponsePackager::RouteRequestAndPackageResponse(const char* request, std::string& header, std::string& body)
{
	std::string body_content = requestRouter.RouteHttpRequest(request);

	if (body_content.length() > 0)
	{
		body = body_head + body_content + body_foot;
		header = header1 + std::to_string(body.length()) + header2;
		return 1;
	}
	return 0;
}



