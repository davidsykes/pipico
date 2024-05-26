#pragma once
#include  <stdint.h>

typedef struct SYSTEM_INTERFACE_T_ {
    const uint8_t* (*load_flash_data)();
    void (*write_flash_data)(const uint8_t* data);
} SYSTEM_INTERFACE_T;

#ifdef __cplusplus
extern "C" {
#endif
   void SetUpSystemInterface(SYSTEM_INTERFACE_T* systemInterface);
#ifdef __cplusplus
}
#endif