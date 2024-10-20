#pragma once
#include <string>
#include <vector>
#include "flash_parameter.h"

class IFlashWriter
{
public:
    virtual bool WriteParameters(const std::vector<FlashParameter> parameters) = 0;
};
