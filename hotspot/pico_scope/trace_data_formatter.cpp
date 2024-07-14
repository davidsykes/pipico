#include "pico_scope.h"
#include <sstream>

#include <string>
#include <iomanip>

const std::string prefix = "{\"type\":\"trace\",\"data\":\"";

void output_int(std::stringstream& s, int i);
void output_word(std::stringstream& s, int i);
void output_byte(std::stringstream& s, int i);

std::string TraceDataFormatter::FormatTraceData(const PicoScopeTrace& trace)
{
    std::stringstream s;
    s << prefix;
    s << std::hex;
    output_int(s, 0x12345678);

    size_t sample_count = trace.changes.size();
    output_int(s, sample_count);

    if (sample_count > 0)
    {
        int trace_length_us = trace.changes[sample_count - 1];
        output_int(s, trace_length_us);

        int value = trace.start_value;
        output_int(s, 0);
        s << value;

        for (int i = 0; i < sample_count; ++i)
        {
            unsigned int change = trace.changes[i];
            value = 1 - value;
            output_int(s, change);
            s << value;
        }
    }

    s << "\"}";
    return s.str();
}

void output_int(std::stringstream& s, int i)
{
    output_word(s, i);
    output_word(s, i >> 16);
}

void output_word(std::stringstream& s, int i)
{
    output_byte(s, i);
    output_byte(s, i >> 8);
}

void output_byte(std::stringstream& s, int i)
{
    s << ((i >> 4) & 15);
    s << (i & 15);
}