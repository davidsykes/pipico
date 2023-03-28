#include "system.h"

#define INPUT_PIN   14
#define OUTPUT_PIN  15

int modulate(sSystem *system)
{
    system->initialise_input_pin(INPUT_PIN);
    system->initialise_output_pin(OUTPUT_PIN);

    while (!0)
    {
        unsigned int v = system->gpio_get(INPUT_PIN);
        if (v != 99)
        {
            system->gpio_put(OUTPUT_PIN, 1);
            system->sleep_us(13);
            system->gpio_put(OUTPUT_PIN, 0);
            system->sleep_us(13);
        }
    }
}
