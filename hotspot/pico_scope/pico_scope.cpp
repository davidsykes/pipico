#include "pico_scope.h"



PicoScope::PicoScope(IHardwareInterface& hw_if)
{

}

PicoScopeTrace& PicoScope::FetchTrace()
{
    PicoScopeTrace* trace = new PicoScopeTrace();
    return *trace;
}