
typedef struct REQUEST_PROCESSOR_T_ {
    void *data_object;
    void (*process_data)(void *data_object, const char *data);
} REQUEST_PROCESSOR_T;


#ifdef __cplusplus
extern "C" {
#endif
int tcp_client_initialise(const char* ssid, const char* password);
int tcp_client_run(REQUEST_PROCESSOR_T* processor, const char* server_ip, uint port);
#ifdef __cplusplus
}
#endif

