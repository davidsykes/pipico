#pragma once
#include <string>


class PicoScopeTrace
{
public:
    const char* gethtml();
};

class PicoScope
{
public:
    PicoScopeTrace& FetchTrace();
};
