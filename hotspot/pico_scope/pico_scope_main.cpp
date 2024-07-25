#include <stdio.h>
#include "pico_scope_main.h"
#include "rest.h"
#include "pico_scope.h"


#define SCOPE_API_SERVER_IP "192.168.1.87"
#define SCOPE_API_PORT 5000

void run_scope(IHardwareInterface& hwif)
{
    printf("Run scope\n");

    hwif.initialise_input_pin(5);
    hwif.gpio_set_pull_up(5,1);

    RestHandler rest(hwif, SCOPE_API_SERVER_IP, SCOPE_API_PORT);
    PicoScope scope(hwif, 100000);
    TraceDataFormatter traceFormatter;

    //while(1)
    {
        hwif.set_led(1);
        PicoScopeTrace& trace = scope.FetchTrace();

        hwif.set_led(0);
        std::string traceData = traceFormatter.FormatTraceData(trace);
        std::string result = rest.Put("/scope", traceData.c_str());
        printf("Scope result %s\n", result.c_str());
        if (result != "Ok")
        {
            rest.Log();
        }
    }
}

