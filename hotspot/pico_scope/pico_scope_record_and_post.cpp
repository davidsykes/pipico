#include <stdio.h>
#include "pico_scope_record_and_post.h"
#include "rest_handler.h"
#include "tcp_response_analyser.h"
#include "pico_scope.h"

#define SCOPE_API_SERVER_IP "192.168.1.87"
#define SCOPE_API_PORT 5000
#define TRACE_DATA_CREATE_URL "/trace"

std::string PicoScopeRecordAndPost::RecordAndPostTrace()
{
    printf("RECORD AND POST\n");
    run_scope(hw_if, config, restHandler);
    return "RECORD AND POST";
}

void run_scope(IHardwareInterface& hw_if, PicoScopeConfiguration& config, IRestHandler& rest)
{
    printf("Run scope on pin %d\n", config.pin);

    hw_if.initialise_input_pin(config.pin);
    hw_if.gpio_set_pull_up(config.pin, 1);

    //TcpResponseAnalyser tcpResponseAnalyser;
    //RestHandler rest_imp(hw_if,
    //                 tcpResponseAnalyser,
    //                 SCOPE_API_SERVER_IP, SCOPE_API_PORT);
    //IRestHandler& rest = rest_imp;
    PicoScope scope(hw_if, 100000);
    TraceDataFormatter traceFormatter;

    //while(1)
    {
        hw_if.set_led(1);
        PicoScopeTrace& trace = scope.FetchTrace();

        hw_if.set_led(0);
        std::string traceData = traceFormatter.FormatTraceData(trace);
        std::string result = rest.Put(TRACE_DATA_CREATE_URL, traceData.c_str());
        printf("Scope result %s\n", result.c_str());
        if (result != "Ok")
        {
            //rest.Log();
        }
    }
}

