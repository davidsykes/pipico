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