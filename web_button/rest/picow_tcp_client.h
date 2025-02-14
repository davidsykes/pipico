
#ifdef __cplusplus
extern "C" {
#endif



int pico_tcp_client_request(const char* server_ip,
                         uint port,
                         const char* request,
                         char*result,
                         int max_result_length);


#ifdef __cplusplus
}
#endif
