#include <stdio.h>
#include "pico_scope_recorder.h"
#include "pico_scope.h"

#define SCOPE_API_SERVER_IP "192.168.1.87"
#define SCOPE_API_PORT 5000
#define TRACE_DATA_CREATE_URL "/trace"

std::string PicoScopeRecorder::RecordTrace()
{
    printf("RECORD AND POST\n");
    return run_scope(hw_if, config);
}

std::string run_scope(IHardwareInterface& hw_if, PicoScopeConfiguration& config)
{
    printf("Run scope on pin %d\n", config.pin);

    hw_if.initialise_input_pin(config.pin);
    hw_if.gpio_set_pull_up(config.pin, 1);

    PicoScope scope(hw_if, 100000);
    TraceDataFormatter traceFormatter;

    hw_if.set_led(1);
    PicoScopeTrace& trace = scope.FetchTrace();

    hw_if.set_led(0);
    std::string traceData = traceFormatter.FormatTraceData(trace);

    return traceData;
}

