#pragma once
#include <string>

class IrCode
{
public:
    std::string Name;
    int Count = 0;
    std::vector<int> Times;
    std::vector<char> Values;
};
