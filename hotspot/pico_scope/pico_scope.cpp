#include "pico_scope.h"

#define SCOPE_TIMEOUT   500000


PicoScope::PicoScope(IHardwareInterface& hw_if) : hw_if(hw_if)
{
}


PicoScopeTrace& PicoScope::FetchTrace(int pin)
{
    int next_trace_value = GPIO_ON_VALUE - hw_if.gpio_get(pin);
    trace.Reset(next_trace_value);

    uint64_t start_time = hw_if.get_time_us();

    while (true)
    {
        uint64_t change = hw_if.wait_value(pin, next_trace_value, SCOPE_TIMEOUT);
        if (change > 0)
        {
            trace.AddChange((int)(change - start_time));
            next_trace_value = GPIO_ON_VALUE - next_trace_value;
        }
        else
        {
            break;
        }
    }

    return trace;
}