#pragma once
#include  <stdint.h>

typedef struct SYSTEM_INTERFACE_T_ {
    int (*fn)(void *p);
    const uint8_t* (*load_flash_data)();
} SYSTEM_INTERFACE_T;

#ifdef __cplusplus
extern "C" {
#endif
   void SetUpSystemInterface(SYSTEM_INTERFACE_T* systemInterface);
#ifdef __cplusplus
}
#endif