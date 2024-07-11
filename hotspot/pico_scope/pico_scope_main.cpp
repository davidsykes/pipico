#include <stdio.h>
#include "pico_scope_main.h"
#include "rest.h"
#include "pico_scope.h"
#include "response_processor.h"


#define SCOPE_API_SERVER_IP "192.168.1.87"
#define SCOPE_API_PORT 5000

void run_scope(IHardwareInterface& hwif)
{
    printf("Run scope\n");

    ResponseProcessor responseProcessor;
    RestHandler rest(hwif, SCOPE_API_SERVER_IP, SCOPE_API_PORT, responseProcessor);
    PicoScope scope(hwif, 100000);

    //while(1)
    {
        hwif.set_led(1);
        PicoScopeTrace& trace = scope.FetchTrace();

        hwif.set_led(0);
        std::string result = rest.Put("/scope", trace.gethtml().c_str());
        printf("Scope result %s\n", result.c_str());
    }
}

