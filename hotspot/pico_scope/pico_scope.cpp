#include "pico_scope.h"



PicoScope::PicoScope(IHardwareInterface& hw_if, int timeout_us)
    : hw_if(hw_if), timeout_us(timeout_us)
{
}


PicoScopeTrace& PicoScope::FetchTrace()
{
    int pin_values_before_signal = hw_if.get_pins();
    int first_signal_value;
    do
    {
        first_signal_value = hw_if.get_pins();
    } while (pin_values_before_signal == first_signal_value);

    uint64_t signal_start = hw_if.get_time_us();
    trace.Reset(pin_values_before_signal, first_signal_value);

    sPinsChangeData cd{};
    cd.current_value = first_signal_value;
    cd.time_us = signal_start;

    while (hw_if.wait_pins_change(&cd, timeout_us))
    {
        trace.AddChange(cd.new_value, (int)(cd.time_us - signal_start));
        cd.current_value = cd.new_value;
    }

    return trace;
}