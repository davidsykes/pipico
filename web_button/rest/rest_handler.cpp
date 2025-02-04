#include <cstring>
#include <sstream>
#include "rest_handler.h"


std::string RestHandler::Get(const char* url)
{
    std::string request = "GET ";
    request += url;

request = "GET /currenttrack HTTP/1.1\r\n"
"Accept: */*\r\n"
//"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\n"
//"Accept-Encoding: gzip, deflate\r\n"
//"Accept-Language: en-GB,en-US;q=0.9,en;q=0.8\r\n"
//"Cache-Control: max-age=0\r\n"
"Host: 192.168.1.126:5001\r\n"
//"Upgrade-Insecure-Requests: 1\r\n"
//"User-Agent: Mozilla/5.0 (X11; CrOS x86_64 14541.0.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36\r\n"
"\r\n";

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