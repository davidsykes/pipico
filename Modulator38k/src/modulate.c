#include "system.h"
#include "gpio_pin.h"

#define INPUT_PIN   16
#define OUTPUT_PIN  22

int modulate(sSystem *system)
{
    system->initialise_input_pin(INPUT_PIN);
    system->initialise_output_pin(OUTPUT_PIN);

    sGPIOPin* ipin = create_gpio_pin(system, INPUT_PIN);
    sGPIOPin* opin = create_gpio_pin(system, OUTPUT_PIN);

    while (!0)
    {
        unsigned int v = ipin->gpio_get(ipin);
        if (v != 0)
        {
            opin->gpio_put(opin, 1);
            system->sleep_us(13);
            opin->gpio_put(opin, 0);
            system->sleep_us(13);
        }
    }
}
