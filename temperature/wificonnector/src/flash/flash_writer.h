#pragma once
#include <string>
#include <vector>
#include <memory>
#include "flash_parameter.h"
#include "flash_hardware.h"


class IFlashWriter
{
public:
    virtual bool WriteParameters(const std::vector<FlashParameter> parameters) = 0;
};

class FlashWriter : public IFlashWriter
{
    IFlashHardware& flashHardware;

    std::unique_ptr<uint8_t> data_block;

    virtual bool WriteParameters(const std::vector<FlashParameter> parameters);


public:
    FlashWriter(IFlashHardware& flashHardware);
};
