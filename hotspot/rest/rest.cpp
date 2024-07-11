#include <cstring>
#include <sstream>
#include "rest.h"


RestHandler::RestHandler(IHardwareInterface& hwif,
                            const char* server,
                            unsigned int port,
                            ResponseProcessor& responseProcessor)
    : hwif(hwif), server(server), port(port), responseProcessor(responseProcessor)
{

}

std::string RestHandler::Get(const char* url)
{
    return hwif.tcp_request(server.c_str(), port, url);

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

    std::string response = hwif.tcp_request(server.c_str(), port, s.str().c_str());
    return responseProcessor.ProcessResponse(response);
}