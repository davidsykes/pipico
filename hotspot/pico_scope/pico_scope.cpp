#include "pico_scope.h"



PicoScope::PicoScope(IHardwareInterface& hw_if, int timeout_us)
    : hw_if(hw_if), timeout_us(timeout_us)
{
    for (int x = 0; x < 16; x++)
    {
        hw_if.initialise_input_pin(x);
        hw_if.gpio_set_pull_up(x, 1);
    }
}

#define SIGNAL_MASK 0xff00
#define SIGNAL_SHIFT 8

int PicoScope::GetSignalPins()
{
    return (hw_if.get_pins() & SIGNAL_MASK) >> SIGNAL_SHIFT;
}

PicoScopeTrace& PicoScope::FetchTrace()
{
    int pin_values_before_signal = GetSignalPins();
    printf("Pins before %d\n", pin_values_before_signal);
    int first_signal_value;
    do
    {
        first_signal_value = GetSignalPins();
    } while (pin_values_before_signal == first_signal_value);
    printf("Pins after %d\n", first_signal_value);

    uint64_t signal_start = hw_if.get_time_us();
    trace.Reset(pin_values_before_signal, first_signal_value);

    sPinsChangeData cd{};
    cd.current_value = first_signal_value;
    cd.time_us = signal_start;

    while (hw_if.wait_pins_change(&cd, SIGNAL_MASK, timeout_us))
    {
        int new_value = cd.new_value >> SIGNAL_SHIFT;
        trace.AddChange(new_value, (int)(cd.time_us - signal_start));
        cd.current_value = cd.new_value;
    }

    return trace;
}