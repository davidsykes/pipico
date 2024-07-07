#include <stdio.h>
#include "work.h"
#include "hardware_interface.hpp"
#include "pico_scope/pico_scope.h"
#include "rest.h"
#include "../tools/hex_dump.h"

#define WIFI_SSID "a907"
#define WIFI_PASSWORD "?thisistheWIFIyouhavebeenlookingfor1398"

// const char* get_message(void *data_object)
// {
//     Worker* worker = (Worker*) data_object;
//     return "";
// }

// void process_data(void *data_object, const char *data)
// {
//     printf("Received Packet\n'%s'-------\n", data);
//     Worker* worker = (Worker*) data_object;
//     printf("Worker %d\n", worker->number());
// }

int do_work(IHardwareInterface& hwif)
{
    hwif.set_led(1);
    
    int config =
        hwif.gpio_get(5) * 8 +
        hwif.gpio_get(4) * 4 +
        hwif.gpio_get(3) * 2 +
        hwif.gpio_get(15);
    printf("Config %d\n", config);
    
    int value = hwif.gpio_get(15);
    printf("Start value %d\n");
    uint64_t t = hwif.wait_value(15, 1-value, 10000000);
    printf("Change %d\n", (int)t);

    PicoScope scope = PicoScope(hwif, 100000);
    PicoScopeTrace trace = scope.FetchTrace(15);
    printf("Trace %s\n", trace.gethtml().c_str());

    hwif.initialise_wifi(WIFI_SSID, WIFI_PASSWORD);

    RestHandler rest(hwif);
    std::string response = rest.Get("/codes");
    printf("Get Response:\n%s---\n", response.c_str());

    std::string hexd = HexDump().Dump(response);
    printf("hexd %s\n", hexd.c_str());
    response = rest.Put("/log");
    printf("Put Response:\n%s---\n", response.c_str());

    hwif.tcp_client_uninit();
    return 0;
}