#include "system.h"
#include "gpio_pin.h"

#define INPUT_PIN   16
#define OUTPUT_PIN  22
// 1000 30.27Khz
// 1255 24.41
#define SLEEP_VALUE 12
#define LOOP_VALUE 306

int modulate(sSystem *system)
{
    system->initialise_input_pin(INPUT_PIN);
    system->initialise_output_pin(OUTPUT_PIN);

    sGPIOPin* ipin = create_gpio_pin(system, INPUT_PIN);
    sGPIOPin* opin = create_gpio_pin(system, OUTPUT_PIN);

    while (!0)
    {
        unsigned int v = ipin->gpio_get(ipin);
        unsigned int count;
        if (v != 0)
        {
            opin->gpio_put(opin, 1);
            system->sleep_us(SLEEP_VALUE+1);
            //count = SLEEP_VALUE;
            //while (--count) {}
            opin->gpio_put(opin, 0);
            system->sleep_us(SLEEP_VALUE);
            //count = LOOP_VALUE;
            //while (--count) {}
        }
    }
}
