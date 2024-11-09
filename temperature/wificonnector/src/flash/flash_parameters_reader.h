#pragma once
#include <string>
#include <vector>
#include "flash_parameter.h"
#include "flash_hardware.h"

class IFlashParametersReader
{
public:
    virtual bool ReadParameters() = 0;
    virtual bool ContainsParameter(const std::string& name) = 0;
    virtual const std::string& GetParameter(const std::string& name) = 0;
};

class FlashParametersReader : public IFlashParametersReader
{
    IFlashHardware& flashHardware;

    const char* flash = 0;
    size_t pointer = 0;
    std::vector<FlashParameter> parameters;
    std::string invalidParameter;

    virtual bool ReadParameters();
    virtual bool ContainsParameter(const std::string& name);
    virtual const std::string& GetParameter(const std::string& name);

    bool HaveWeReachedTheEndOfTheParameters();
    std::string ReadString();
    void ReadAParameter();

public:
    FlashParametersReader(IFlashHardware& flashHardware) : flashHardware(flashHardware) {}
};
