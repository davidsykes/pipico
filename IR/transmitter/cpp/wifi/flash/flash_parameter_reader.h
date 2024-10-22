#pragma once
#include <string>
#include <vector>
#include "flash_parameter.h"
#include "flash_hardware.h"

class IFlashParameterReader
{
public:
    virtual void ReadParameters() = 0;
    virtual bool ContainsParameter(const std::string& name) = 0;
    virtual const std::string& GetParameter(const std::string& name) = 0;
};

class FlashParameterReader : public IFlashParameterReader
{
    IFlashHardware& flashHardware;

    const char* flash = 0;
    int pointer = 0;
    std::vector<FlashParameter> parameters;

    virtual void ReadParameters();
    virtual bool ContainsParameter(const std::string& name);
    virtual const std::string& GetParameter(const std::string& name);

    bool HaveWeReachedTheEndOfTheParameters();
    std::string ReadString();
    void ReadAParameter();

public:
    FlashParameterReader(IFlashHardware& flashHardware) : flashHardware(flashHardware) {}
};
