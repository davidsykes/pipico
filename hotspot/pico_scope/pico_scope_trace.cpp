#include "pico_scope.h"
#include <sstream>


void PicoScopeTrace::Reset(int initial_value, int first_value)
{
    this->initial_value = initial_value;
    values.clear();
    value_times.clear();
    values.push_back(first_value);
    value_times.push_back(0);
}

void PicoScopeTrace::AddChange(int value, int time)
{
    values.push_back(value);
    value_times.push_back(time);
}