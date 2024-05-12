typedef struct HOTSPOT_SEAM_T_ {
    const char *seam_name;
    const char* (*go) (int);
    int (*process_request)(const char *request, const char *params, char *result, size_t max_result_len);
} HOTSPOT_SEAM_T;

#ifdef __cplusplus
extern "C" {
#endif
   int main_hotspot(HOTSPOT_SEAM_T * seam);
#ifdef __cplusplus
}
#endif