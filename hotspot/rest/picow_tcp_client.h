#include "../hw_if/hardware_interface.h"

typedef struct REQUEST_PROCESSOR_T_ {
    void *data_object;
    const char* (*get_message)(void *data_object);
    void (*process_data)(void *data_object, const char *data);
} REQUEST_PROCESSOR_T;


#ifdef __cplusplus
extern "C" {
#endif
int tcp_client_initialise(sHardwareInterface* hw_if, const char* ssid, const char* password);
void run_tcp_client_test(REQUEST_PROCESSOR_T* processor, const char* server_ip, uint port, const char* request, char*result, int max_result_length);
void tcp_client_uninit();
#ifdef __cplusplus
}
#endif

