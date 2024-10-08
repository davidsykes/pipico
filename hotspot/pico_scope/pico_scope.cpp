#include "pico_scope.h"

PicoScope::PicoScope(IHardwareInterface& hw_if, int timeout_us)
    : hw_if(hw_if), timeout_us(timeout_us)
{
}

#define SIGNAL_MASK 0xff0
#define SIGNAL_SHIFT 4

int PicoScope::GetSignalPins()
{
    return (hw_if.get_pins() & SIGNAL_MASK) >> SIGNAL_SHIFT;
}

PicoScopeTrace& PicoScope::FetchTrace()
{
    int pin_values_before_signal = GetSignalPins();
    int first_signal_value;
    do
    {
        first_signal_value = GetSignalPins();
    } while (pin_values_before_signal == first_signal_value);

    uint64_t signal_start = hw_if.get_time_us();
    trace.Reset(pin_values_before_signal, first_signal_value);

    sPinsChangeData cd{};
    cd.current_value = first_signal_value;
    cd.time_us = signal_start;

    while (hw_if.wait_pins_change(&cd, SIGNAL_MASK, timeout_us))
    {
        int new_value = cd.new_value >> SIGNAL_SHIFT;
        trace.AddChange((int)(cd.time_us - signal_start), new_value);
        cd.current_value = cd.new_value;
    }

    return trace;
}