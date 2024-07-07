#include "rest.h"


RestHandler::RestHandler(IHardwareInterface& hwif) : hwif(hwif)
{

}

std::string RestHandler::Get(const char*url)
{
    return hwif.tcp_request(url);

    // char buffer[TCP_BUFFER_LENGTH];
    // run_tcp_client_test(TEST_TCP_SERVER_IP, TCP_PORT, "GET /codes HTTP/1.1\r\nHost: test.com\r\nAccept: */*\r\n\r\n", buffer, TCP_BUFFER_LENGTH);
    // return buffer;
}
std::string RestHandler::Put(const char*url)
{
    return hwif.tcp_request(url);

    // char buffer[TCP_BUFFER_LENGTH];
    // run_tcp_client_test(TEST_TCP_SERVER_IP, TCP_PORT, "GET /codes HTTP/1.1\r\nHost: test.com\r\nAccept: */*\r\n\r\n", buffer, TCP_BUFFER_LENGTH);
    // return buffer;
}