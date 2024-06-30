#pragma once
#include <string>
#include "hardware_interface.hpp"


class PicoScopeTrace
{
public:
    const char* gethtml();
};

class PicoScope
{
public:
    PicoScope(IHardwareInterface& hw_if);
    PicoScopeTrace& FetchTrace();
};
