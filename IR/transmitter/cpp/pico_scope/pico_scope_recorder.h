#pragma once
#include "../hw_if/pico_hardware_interface.h"
#include "pico_scope_configuration.h"

class IPicoScopeRecorder
{
public:
    virtual std::string RecordTrace() = 0;
};

class PicoScopeRecorder : public IPicoScopeRecorder
{
    IHardwareInterface& hw_if;
    PicoScopeConfiguration& config;

    virtual std::string RecordTrace();

public:
    PicoScopeRecorder(IHardwareInterface& hw_if,
                            PicoScopeConfiguration& config)
                            : hw_if(hw_if), config(config) {}
};


std::string run_scope(IHardwareInterface& hw_if, PicoScopeConfiguration& config);

