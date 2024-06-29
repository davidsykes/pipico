#include "pico_scope.h"




PicoScopeTrace& PicoScope::FetchTrace()
{
    PicoScopeTrace* trace = new PicoScopeTrace();
    return *trace;
}