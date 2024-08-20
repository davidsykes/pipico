#pragma once
#include "pico_hardware_interface.h"
#include "pico_scope_configuration.h"

class IPicoScopeRecordAndPost
{
public:
    virtual std::string RecordAndPostTrace() = 0;
};

class PicoScopeRecordAndPost : public IPicoScopeRecordAndPost
{
    IHardwareInterface& hw_if;
    PicoScopeConfiguration& config;

    virtual std::string RecordAndPostTrace();

public:
    PicoScopeRecordAndPost(IHardwareInterface& hw_if,
                            PicoScopeConfiguration& config)
                            : hw_if(hw_if), config(config) {}
};


void run_scope(IHardwareInterface& hw_if, PicoScopeConfiguration& config);

