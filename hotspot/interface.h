int set_up_hotspot(
   const char* hotspot_name,
   const char* hotspot_password,
   int (*process_request)(const char *request, const char *params, char *result, size_t max_result_len),
   const char* (*go) (int));