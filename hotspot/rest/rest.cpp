#include "rest.h"
#include <cstring>
#include <sstream>


RestHandler::RestHandler(IHardwareInterface& hwif) : hwif(hwif)
{

}

std::string RestHandler::Get(const char*url)
{
    return hwif.tcp_request(url);

    // char buffer[TCP_BUFFER_LENGTH];
    // run_tcp_client_test("GET /codes HTTP/1.1\r\nHost: test.com\r\nAccept: */*\r\n\r\n", buffer, TCP_BUFFER_LENGTH);
    // return buffer;
}
std::string RestHandler::Put(const char* url, const char* body)
{
    std::stringstream s;
    s << "PUT " << url;
    s << " HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\n";
    s << "Content-Type: application/json\r\n";
    s << "Content-Length: " << strlen(body) << "\r\n";
    s << "\r\n";
    s << body;

    return hwif.tcp_request(s.str().c_str());
}