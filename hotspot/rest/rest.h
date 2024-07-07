#pragma once
#include <string>
#include "hardware_interface.hpp"

class RestHandler
{
    IHardwareInterface& hwif;
public:
    RestHandler(IHardwareInterface& hwif);
    std::string Get(const char*url);
    std::string Put(const char*url);
};
