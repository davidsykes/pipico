typedef struct HOTSPOT_SEAM_T_ {
    char *seam_name;
    char* (*go) (int);
    int (*process_request)(const char *request, const char *params, char *result, size_t max_result_len);
} HOTSPOT_SEAM_T;

int main_hotspot(HOTSPOT_SEAM_T * seam);