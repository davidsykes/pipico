#include "pico_scope.h"

#define GPIO_ON_VALUE   1
#define SCOPE_TIMEOUT   500000


PicoScope::PicoScope(IHardwareInterface& hw_if) : hw_if(hw_if)
{
}


PicoScopeTrace& PicoScope::FetchTrace(int pin)
{
    int gpio_value = hw_if.gpio_get(pin);
    trace.Reset(gpio_value);

    uint64_t start_time = hw_if.get_time_us();

    while (true)
    {
        int changed_value = GPIO_ON_VALUE - gpio_value;
        uint64_t change = hw_if.wait_value(pin, changed_value, SCOPE_TIMEOUT);
        if (change > 0)
        {
            trace.AddChange(change - start_time);
            gpio_value = changed_value;
        }
        else
        {
            break;
        }
    }

    return trace;
}