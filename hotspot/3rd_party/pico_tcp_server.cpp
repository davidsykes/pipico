#include "pico_tcp_server.h"
#include <cstring>


int make_error(TCP_CONNECT_STATE_T* con_state, int error, const char*message)
{
    con_state->header_len = snprintf(con_state->headers, sizeof(con_state->headers),
    "HTTP/1.1 %d\r\nContent-Length: %d\r\n\r\n", error, strlen(message));
    con_state->result_len = snprintf(con_state->result, sizeof(con_state->result), "%s", message);
    return 1;
}

int process_http_request(TCP_CONNECT_STATE_T* con_state)
{
    std::string headers(con_state->headers);
    std::string request = headers.substr(0, headers.find('\r'));
    printf("Request: %s\n", request.c_str());

    HttpRequestRouter* router = (HttpRequestRouter*)con_state->http_request_handler;
    std::string header;
    std::string body;
    if (router->HandleHttpRequest(con_state->headers, header, body))
    {
        con_state->header_len = header.length();
        con_state->result_len = body.length();
        if ((con_state->header_len >= sizeof(con_state->headers)) || (con_state->result_len >= sizeof(con_state->result)))
        {
            return make_error(con_state, 500,"Response length exceeded");
        }
        strcpy(con_state->headers, header.c_str());
        strcpy(con_state->result, body.c_str());
        return 1;
    }
    return 0;
}

int HttpRequestRouter::HandleHttpRequest(const char* request, std::string& header, std::string& body)
{

    header = "the header";
    body = "the body";

    return 1;
}