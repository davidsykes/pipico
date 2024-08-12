#include "../hw_if/hardware_interface.h"

int run_tcp_client_test(const char* server_ip,
                         uint port,
                         const char* request,
                         char*result,
                         int max_result_length);
void cyw43_arch_deinit();
