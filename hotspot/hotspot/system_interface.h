#pragma once

typedef struct SYSTEM_INTERFACE_T_ {
    int (*fn)(void *p);
} SYSTEM_INTERFACE_T;

#ifdef __cplusplus
extern "C" {
#endif
   void SetUpSystemInterface(SYSTEM_INTERFACE_T* systemInterface);
#ifdef __cplusplus
}
#endif