#include "rest.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "picow_tcp_client.h"
#ifdef __cplusplus
}
#endif

#define TEST_TCP_SERVER_IP "192.168.1.87"
#define TCP_PORT 5000
#define TCP_BUFFER_LENGTH   2048

std::string RestHandler::Get(const char*url)
{
    char buffer[TCP_BUFFER_LENGTH];
    run_tcp_client_test(TEST_TCP_SERVER_IP, TCP_PORT, "GET /codes HTTP/1.1\r\nHost: test.com\r\nAccept: */*\r\n\r\n", buffer, TCP_BUFFER_LENGTH);
    return buffer;
}
std::string RestHandler::Put(const char*url)
{
    char buffer[TCP_BUFFER_LENGTH];
    run_tcp_client_test(TEST_TCP_SERVER_IP, TCP_PORT, "PUT /log HTTP/1.1\r\nHost: test.com\r\nAccept: */*\r\n\r\n", buffer, TCP_BUFFER_LENGTH);
    return buffer;
}