#pragma once
#include "pico_hardware_interface.h"
#include "pico_scope_configuration.h"
#include "../rest/rest_handler.h"

class IPicoScopeRecordAndPost
{
public:
    virtual std::string RecordAndPostTrace() = 0;
};

class PicoScopeRecordAndPost : public IPicoScopeRecordAndPost
{
    IHardwareInterface& hw_if;
    PicoScopeConfiguration& config;
    IRestHandler& restHandler;

    virtual std::string RecordAndPostTrace();

public:
    PicoScopeRecordAndPost(IHardwareInterface& hw_if,
                            PicoScopeConfiguration& config,
                            IRestHandler& restHandler)
                            : hw_if(hw_if), config(config), restHandler(restHandler) {}
};


void RunScope(IHardwareInterface& hw_if);
void run_scope(IHardwareInterface& hw_if, PicoScopeConfiguration& config, IRestHandler& restHandler);
