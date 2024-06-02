#define FLASH_PAGE_SIZE 256

typedef struct SYSTEM_INTERFACE_T_ {
    const uint8_t* (*read_flash_data)();
    void (*write_flash_data)(const uint8_t* data);
} SYSTEM_INTERFACE_T;

#ifdef __cplusplus
extern "C" {
#endif
void SetUpSystemInterface(SYSTEM_INTERFACE_T* systemInterface);
    // const uint8_t* read_flash_data();
    // void write_flash_data(const uint8_t* flash_data);
#ifdef __cplusplus
}
#endif

// #ifdef __cplusplus
// extern "C" {
// #endif
// #ifdef __cplusplus
// }
// #endif