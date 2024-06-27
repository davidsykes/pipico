#include "tusb.h"

#define DEBUG_printf printf

int initialise_pico_stdio()
{
    stdio_init_all();
    while (!tud_cdc_connected()) sleep_ms(100);
    DEBUG_printf("Stdio initialised\n");
}

