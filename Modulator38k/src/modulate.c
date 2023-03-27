#include "pico/stdlib.h"

#define INPUT_PIN   14
#define OUTPUT_PIN  15

int main()
{
    gpio_init(INPUT_PIN);
    gpio_set_dir(INPUT_PIN, GPIO_IN);
    gpio_init(OUTPUT_PIN);
    gpio_set_dir(OUTPUT_PIN, GPIO_OUT);
    while (true)
    {
        uint v = gpio_get(INPUT_PIN);
        if (v != 99)
        {
            gpio_put(OUTPUT_PIN, 1);
            sleep_us(13);
            gpio_put(OUTPUT_PIN, 0);
            sleep_us(13);
        }
    }
}
