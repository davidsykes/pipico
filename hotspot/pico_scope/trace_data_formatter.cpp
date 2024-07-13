#include "pico_scope.h"
#include <sstream>


const std::string prefix = "{\"code\":\"code\",\"wavepoints\":[";

std::string TraceDataFormatter::FormatTraceData(const PicoScopeTrace& trace)
{
    std::stringstream s;
    s << prefix;
    s << "[" << trace.start_value << ",0]";
    int next_value = GPIO_ON_VALUE - trace.start_value;

    for (int i = 0; i < trace.changes.size(); ++i)
    {
        s << ",[" << next_value << "," << trace.changes[i] << "]";
        next_value = GPIO_ON_VALUE - next_value;
    }

    s << "]}";

    return s.str();
}