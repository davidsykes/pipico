typedef struct HOTSPOT_CONFIGURATION_T_ {
    const char *hotspot_name;
    const char *hotspot_password;
    const char* (*go) (int);
    int (*process_request)(const char *request, const char *params, char *result, size_t max_result_len);
} HOTSPOT_CONFIGURATION_T;

#ifdef __cplusplus
extern "C" {
#endif
   int main_hotspot(HOTSPOT_CONFIGURATION_T * hotspot_configuration);
#ifdef __cplusplus
}
#endif