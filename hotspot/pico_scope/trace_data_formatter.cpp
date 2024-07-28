#include "pico_scope.h"
#include <sstream>



std::string TraceDataFormatter::FormatTraceData(const PicoScopeTrace& trace)
{
    std::stringstream s;
    s << "{\"InitialValue\":";
    s << trace.initial_value;
    s << ",\"Values\":[";

    for (int v = 0; v < trace.values.size(); ++v)
    {
        if (v > 0)
        {
            s << ",";
        }
        s << "[" << trace.value_times[v] << "," << trace.values[v] << "]";
    }

    s << "]}";
    return s.str();
}
