#include "pico_tcp_server.h"



int process_http_request(TCP_CONNECT_STATE_T* con_state)
{
    printf("vvvvvv\n%s\n^^^\n", con_state->headers);

    return 0;
}