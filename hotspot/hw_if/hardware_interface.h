#pragma once
#ifdef _CONSOLE
#include <cinttypes>
#else
#include "pico/types.h"
#endif

typedef struct sHardwareInterface
{
    void (*initialise_pico_stdio)();
    int (*cyw43_arch_init)();
    int (*initialise_wifi)(const char* ssid, const char* password);
    uint64_t (*get_time_us)();
    void (*initialise_input_pin)(int pin_number);
    void (*initialise_output_pin)(int pin_number);
    int (*gpio_get)(int pin_number);
    char (*get_pins)();
    uint64_t (*wait_value)(int pin_number, int value, uint64_t timeout);
    void (*gpio_put)(int pin_number, int value);
    void (*set_led)(int value);
    void (*sleep_us)(int useconds);
    int (*tcp_request)(const char* server_ip,
                         unsigned int port,
                         const char* request,
                         char*result,
                         int max_result_length);
    void (*tcp_client_uninit)();

} sHardwareInterface;


#ifdef __cplusplus
extern "C" {
#endif

sHardwareInterface* create_hardware_interface();

#ifdef __cplusplus
}
#endif
