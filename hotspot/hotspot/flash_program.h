

typedef struct CREDENTIALS_T_ {
    const char *hotspot_name;
    const char *hotspot_password;
} CREDENTIALS_T;


#ifdef __cplusplus
extern "C" {
#endif
    int read_flash_contents(CREDENTIALS_T* credentials);
    int try_out_flash();
    const uint8_t* load_flash_data();
#ifdef __cplusplus
}
#endif