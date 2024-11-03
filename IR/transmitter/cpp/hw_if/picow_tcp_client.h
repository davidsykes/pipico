#include "../hw_if/hardware_interface.h"

int tcp_client_request(const char* server_ip,
                         uint port,
                         const char* request,
                         char*result,
                         int max_result_length);
