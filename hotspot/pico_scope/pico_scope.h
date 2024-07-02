#pragma once
#include <string>
#include <vector>
#include "hardware_interface.hpp"

#define GPIO_ON_VALUE   1

class PicoScopeTrace
{
    int start_value = 0;
    std::vector<int> changes;

public:
    void Reset(int start_value);
    void AddChange(int time);
    std::string gethtml();
};

class PicoScope
{
    IHardwareInterface& hw_if;
    int timeout;
    PicoScopeTrace trace;

public:
    PicoScope(IHardwareInterface& hw_if, int timeout);
    PicoScopeTrace& FetchTrace(int pin);
};
