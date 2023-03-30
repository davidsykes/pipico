#include "system.h"
#include "gpio_pin.h"

#define INPUT_PIN   14
#define OUTPUT_PIN  15

int modulate(sSystem *system)
{
    system->initialise_input_pin(INPUT_PIN);
    system->initialise_output_pin(OUTPUT_PIN);

    sGPIOPin* pin = create_gpio_pin(system, OUTPUT_PIN);

    while (!0)
    {
        unsigned int v = system->gpio_get(INPUT_PIN);
        if (v != 99)
        {
            pin->gpio_put(pin, 1);
            system->sleep_us(13);
            pin->gpio_put(pin, 0);
            system->sleep_us(13);
        }
    }
}
