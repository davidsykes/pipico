#include "pico_tcp_server.h"
#include <cstring>
#include "http_response_packager.h"

//#define DEBUG_REQUEST_RESPONSE

static int make_error(TCP_CONNECT_STATE_T* con_state, int error, const char*message)
{
    con_state->header_len = snprintf(con_state->headers, sizeof(con_state->headers),
    "HTTP/1.1 %d\r\nContent-Length: %d\r\n\r\n", error, strlen(message));
    con_state->result_len = snprintf(con_state->result, sizeof(con_state->result), "%s", message);
    return 1;
}

int process_http_request(TCP_CONNECT_STATE_T* con_state)
{
    std::string headers(con_state->headers);
#ifdef DEBUG_REQUEST_RESPONSE
    std::string request = headers.substr(0, headers.find('\r'));
    printf("TCP Request: %s\n", request.c_str());
#endif

    IHttpResponsePackager* router = (IHttpResponsePackager*)con_state->http_request_handler;
    std::string header;
    std::string body;
    if (router->RouteRequestAndPackageResponse(con_state->headers, header, body))
    {
        con_state->header_len = header.length();
        con_state->result_len = body.length();
#ifdef DEBUG_REQUEST_RESPONSE
        printf("Header: %s\n", header.c_str());
        printf("Body: %s\n", body.c_str());
#endif
        if ((con_state->header_len >= sizeof(con_state->headers)) || (con_state->result_len >= sizeof(con_state->result)))
        {
#ifdef DEBUG_REQUEST_RESPONSE
            printf("RESPOSE LENGTH EXCEEDED: %d,%d > %d,%d\n",
            con_state->header_len,
            con_state->result_len,
            sizeof(con_state->headers),
            sizeof(con_state->result));
#endif
            return make_error(con_state, 500,"Response length exceeded");
        }
        strcpy(con_state->headers, header.c_str());
        strcpy(con_state->result, body.c_str());
        return 1;
    }
    return 0;
}
