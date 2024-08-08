#pragma once
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    int main_hotspot(
     const char *hotspot_name,
     const char *hotspot_password,
     void *configuration
     );
     // TODO Factor this out to a server object
    int run_tcp_server(void *request_processor);
#ifdef __cplusplus
}
#endif

typedef struct TCP_REQUEST_PROCESSOR_T_ {
    void *configuration; // TODO Rename to request_processor
    size_t (*process_request)(void *configuration, const char *request, const char *params, char *result, size_t max_result_len);
} TCP_REQUEST_PROCESSOR_T;


