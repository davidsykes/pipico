#pragma once
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    int initialise_pico_stdio();
   int main_hotspot(
    const char *hotspot_name,
    const char *hotspot_password,
    void *configuration
    );
#ifdef __cplusplus
}
#endif

typedef struct REQUEST_PROCESSOR_T_ {
    void *configuration;
    size_t (*process_request)(void *configuration, const char *request, const char *params, char *result, size_t max_result_len);
} REQUEST_PROCESSOR_T;


