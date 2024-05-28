

typedef struct CREDENTIALS_T_ {
    const char *hotspot_name;
    const char *hotspot_password;
} CREDENTIALS_T;


#ifdef __cplusplus
extern "C" {
#endif
    const uint8_t* load_flash_data();
    void write_flash_data(const uint8_t* flash_data);
#ifdef __cplusplus
}
#endif