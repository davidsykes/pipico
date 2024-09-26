#pragma once
#ifdef _CONSOLE
#include <cinttypes>
#else
#include "pico/types.h"
#endif
#include "pins_changed_data.h"

typedef struct sHardwareInterface
{
    void (*initialise_pico_stdio)(bool wait_for_usb_comms);
    int (*cyw43_arch_init)();
    int (*initialise_wifi)(const char* ssid, const char* password);
    uint64_t (*get_time_us)();
    void (*initialise_input_pin)(int pin_number);
    void (*gpio_set_pull_up)(int pin_number, int value);
    void (*initialise_output_pin)(int pin_number);
    int (*gpio_get)(int pin_number);
    int (*get_pins)();
    int (*wait_pins_change)(sPinsChangeData* pins_change_data, int mask, uint64_t timeout);
    void (*gpio_put)(int pin_number, int value);
    uint64_t (*gpio_put_at_us)(int pin_number, bool value, uint64_t time_us);
    void (*set_led)(int value);
    void (*sleep_us)(int useconds);
    int (*tcp_request)(const char* server_ip,
                         unsigned int port,
                         const char* request,
                         char*result,
                         int max_result_length);
    void (*cyw43_arch_deinit)();

} sHardwareInterface;


#ifdef __cplusplus
extern "C" {
#endif

sHardwareInterface* create_hardware_interface();

#ifdef __cplusplus
}
#endif
