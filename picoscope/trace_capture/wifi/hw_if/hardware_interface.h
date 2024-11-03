#pragma once
#include <stdbool.h>

typedef struct sHardwareInterface
{
    void (*initialise_pico_stdio)(bool wait_for_usb_comms);
    int (*cyw43_arch_init)();
    int (*initialise_wifi_sta)(const char* ssid, const char* password);
    void (*initialise_wifi_ap)(const char* ssid, const char* password);
} sHardwareInterface;


#ifdef __cplusplus
extern "C" {
#endif

sHardwareInterface* create_hardware_interface();

#ifdef __cplusplus
}
#endif
