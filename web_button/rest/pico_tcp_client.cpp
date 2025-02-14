#include "pico_tcp_client.h"
#include "picow_tcp_client.h"

#define TCP_BUFFER_LENGTH   2048

int PicoTcpClient::tcp_request(const char* server, unsigned int port, const char* request, std::string& response)
{
    #ifdef DEBUG_TCP_REQUEST
    printf("---TCP REQUEST---\n%s\n^^^\n", request);
    #endif
    char buffer[TCP_BUFFER_LENGTH];
    buffer[0] = 0;
    int result = pico_tcp_client_request(server, port, request, buffer, TCP_BUFFER_LENGTH);
    if (result == 0)
    {
        response = buffer;
        #ifdef DEBUG_TCP_REQUEST
        printf("---TCP RESPONSE---\n%s\n^^^\n", response.c_str());
        #endif
    }
    return result;
}

