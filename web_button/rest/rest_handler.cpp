#include <cstring>
#include <sstream>
#include "rest_handler.h"


std::string RestHandler::Get(const char* url)
{
    std::string request = "GET ";
    request += url;
    std::string response;
    tcpRequestMaker.MakeRequest(request, response);
    return response;
}

std::string RestHandler::Put(const char* url, const char* body)
{
    std::string request = MakeRequest(url, body);

    std::string response;
    tcpRequestMaker.MakeRequest(request, response);
    return response;
}

std::string RestHandler::MakeRequest(const char* url, const char* body)
{
    std::ostringstream s;
    s << "PUT " << url << " HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\n";
    s << "Content-Type: application/json\r\n";
    s << "Content-Length: " << strlen(body) << "\r\n";
    s << "\r\n";
    s << body;
    return s.str();
}