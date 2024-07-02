#include "pico_scope.h"
#include <sstream>



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
    s << start_value;

    for (int i = 0; i < changes.size(); ++i)
    {
        s << ",";
        s << changes[i];
    }

    return s.str();
}