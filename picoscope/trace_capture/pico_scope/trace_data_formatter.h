#pragma once
#include <string>
#include "pico_scope.h"

class TraceDataFormatter
{
public:
    std::string FormatTraceData(const PicoScopeTrace& trace);
};

