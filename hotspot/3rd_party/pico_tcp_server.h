#pragma once
#include "lwip/tcp.h"

typedef struct TCP_CONNECT_STATE_T_ {
    struct tcp_pcb *pcb;
    int sent_len;
    char headers[128];
    char result[256];
    int header_len;
    int result_len;
    ip_addr_t *gw;
} TCP_CONNECT_STATE_T;

#ifdef __cplusplus
extern "C" {
#endif
int process_http_request(TCP_CONNECT_STATE_T* con_state);
#ifdef __cplusplus
}
#endif
