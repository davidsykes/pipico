#pragma once
#include <vector>
#include "../hw_if/ihardware_interface.h"

class PicoScopeTrace
{
public:
    int initial_value = 0;
    std::vector<int> value_times;
    std::vector<int> values;

    void Reset(int initial_value, int first_value);
    void AddChange(int time, int value);
};

class IPicoScope
{
public:
    virtual PicoScopeTrace& FetchTrace() = 0;
};

class PicoScope : public IPicoScope
{
    IHardwareInterface& hw_if;
    int timeout_us;
    PicoScopeTrace trace;

    int GetSignalPins();

    virtual PicoScopeTrace& FetchTrace();

public:
    PicoScope(IHardwareInterface& hw_if, int timeout_us);
};

