

typedef struct CREDENTIALS_T_ {
    const char *hotspot_name;
    const char *hotspot_password;
} CREDENTIALS_T;


#ifdef __cplusplus
extern "C" {
#endif
    bool read_flash_contents(CREDENTIALS_T* credentials);
    int try_out_flash();
#ifdef __cplusplus
}
#endif