#include "pico_scope.h"
#include <sstream>


const std::string prefix = "{\"code\":\"code\",\"wavepoints\":[";

void PicoScopeTrace::Reset(int start_value)
{
    this->start_value = start_value;
    changes.clear();
}

void PicoScopeTrace::AddChange(int time)
{
    changes.push_back(time);
}

std::string PicoScopeTrace::gethtml()
{
    std::stringstream s;
    s << prefix;
    s << "[" << start_value << ",0]";
    int next_value = GPIO_ON_VALUE - start_value;

    for (int i = 0; i < changes.size(); ++i)
    {
        s << ",[" << next_value << "," << changes[i] << "]";
        next_value = GPIO_ON_VALUE - next_value;
    }

    s << "]}";

    return s.str();
}