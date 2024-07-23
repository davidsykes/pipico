#pragma once
#include <string>
#include <vector>
#include "hardware_interface.hpp"

class PicoScopeTrace
{
public:
    int initial_value = 0;
    std::vector<int> values;
    std::vector<int> value_times;

    void Reset(int initial_value, int first_value);
    void AddChange(int value, int time);
};

class PicoScope
{
    IHardwareInterface& hw_if;
    int timeout_us;
    PicoScopeTrace trace;

    int GetSignalPins();

public:
    PicoScope(IHardwareInterface& hw_if, int timeout_us);
    PicoScopeTrace& FetchTrace();
};

class TraceDataFormatter
{
public:
    std::string FormatTraceData(const PicoScopeTrace& trace);
};