#include "pico_scope.h"
#include <sstream>



std::string TraceDataFormatter::FormatTraceData(const PicoScopeTrace& trace)
{
    std::stringstream s;
    s << "{\"InitialValue\":";
    s << trace.initial_value;
    s << ",\"values\":{";

    for (int v = 0; v < trace.values.size(); ++v)
    {
        if (v > 0)
        {
            s << ",";
        }
        s << "{" << trace.values[v] << "," << trace.value_times[v] << "}";
    }

    s << "}}";
    return s.str();
}