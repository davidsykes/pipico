#pragma once
#include <string>
#include "hardware_interface.hpp"


class PicoScopeTrace
{
public:
    void Reset(int start_value);
    void AddChange(int time);
    const char* gethtml();
};

class PicoScope
{
    IHardwareInterface& hw_if;
    PicoScopeTrace trace;

public:
    PicoScope(IHardwareInterface& hw_if);
    PicoScopeTrace& FetchTrace(int pin);
};
