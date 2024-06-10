
typedef struct REQUEST_PROCESSOR_T_ {
    void *data_object;
    void (*process_data)(void *data_object, const char *data);
} REQUEST_PROCESSOR_T;


#ifdef __cplusplus
extern "C" {
#endif
int tcp_client_main(REQUEST_PROCESSOR_T* processor);
#ifdef __cplusplus
}
#endif

