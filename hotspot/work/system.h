#pragma once

typedef struct sSystem
{
    void (*initialise_input_pin)(int pin_number);
    void (*initialise_output_pin)(int pin_number);
    int (*gpio_get)(int pin_number);
    void (*gpio_put)(int pin_number, int value);
    void (*sleep_us)(int useconds);

} sSystem;