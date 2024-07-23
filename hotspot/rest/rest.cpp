#include <cstring>
#include <sstream>
#include "rest.h"


RestHandler::RestHandler(IHardwareInterface& hwif,
                            ITcpResponseAnalyser& tcp_analyser,
                            const char* server,
                            unsigned int port)
    : hwif(hwif), tcp_analyser(tcp_analyser), server(server), port(port)
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
    s << "PUT " << url << " HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\n";
    s << "Content-Type: application/json\r\n";
    s << "Content-Length: " << strlen(body) << "\r\n";
    s << "\r\n";
    s << body;
    last_request = s.str();

    last_response = hwif.tcp_request(server.c_str(), port, last_request.c_str());
    
    tcp_analyser.AnalyseTcpResponse(last_request, last_response);
    
    return last_response;
}

void RestHandler::Log()
{
    std::stringstream s;
    s << last_request << "\r\n\r\n" << last_response;

    Put("/log", s.str().c_str());
}