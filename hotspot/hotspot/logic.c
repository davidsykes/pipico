#include "tusb.h"

int initialise_pico()
{
    stdio_init_all();
    while (!tud_cdc_connected()) sleep_ms(100);
    printf("Stdio initialised\n");
}

