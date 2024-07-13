#pragma once
#include <string>
#include <vector>
#include "hardware_interface.hpp"

#define GPIO_ON_VALUE   1

class PicoScopeTrace
{
public:
    int start_value = 0;
    std::vector<int> changes;

    void Reset(int start_value);
    void AddChange(int time);
};

class PicoScope
{
    IHardwareInterface& hw_if;
    int timeout_us;
    PicoScopeTrace trace;

public:
    PicoScope(IHardwareInterface& hw_if, int timeout_us);
    PicoScopeTrace& FetchTrace(int pin);
};

class TraceDataFormatter
{
public:
    std::string FormatTraceData(const PicoScopeTrace& trace);
};