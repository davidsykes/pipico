#pragma once

typedef struct sHardwareInterface
{
    void (*initialise_pico_stdio)();
    int (*cyw43_arch_init)();
    void (*initialise_input_pin)(int pin_number);
    void (*initialise_output_pin)(int pin_number);
    int (*gpio_get)(int pin_number);
    void (*gpio_put)(int pin_number, int value);
    void (*set_led)(int value);
    void (*sleep_us)(int useconds);

} sHardwareInterface;


#ifdef __cplusplus
extern "C" {
#endif

sHardwareInterface* create_hardware_interface();

#ifdef __cplusplus
}
#endif

