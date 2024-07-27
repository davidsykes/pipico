#include <cstring>
#include <sstream>
#include "rest_handler.h"


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
    std::string request = MakeRequest(url, body);

    std::string response = PutRaw(request);

    if (!tcp_analyser.AnalyseTcpResponse(request, response))
    {
        LogLastRequest(request, response);
    }

    return response;
}

std::string RestHandler::PutRaw(const std::string& request)
{
    return hwif.tcp_request(server.c_str(), port, request.c_str());
}

void RestHandler::LogLastRequest(const std::string& request, const std::string& response)
{
    std::stringstream s;
    s << request << "\r\n\r\n" << response;

    PutRaw(MakeRequest("/log", s.str().c_str()));
}

std::string RestHandler::MakeRequest(const char* url, const char* body)
{
    std::stringstream s;
    s << "PUT " << url << " HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\n";
    s << "Content-Type: application/json\r\n";
    s << "Content-Length: " << strlen(body) << "\r\n";
    s << "\r\n";
    s << body;
    return s.str();
}