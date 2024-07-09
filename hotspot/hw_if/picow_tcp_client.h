#include "../hw_if/hardware_interface.h"

typedef struct REQUEST_PROCESSOR_T_ {
    void *data_object;
    const char* (*get_message)(void *data_object);
    void (*process_data)(void *data_object, const char *data);
} REQUEST_PROCESSOR_T;

int tcp_client_initialise(const char* ssid, const char* password);
int run_tcp_client_test(const char* server_ip,
                         uint port,
                         const char* request,
                         char*result,
                         int max_result_length);
void tcp_client_uninit();
