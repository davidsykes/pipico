#pragma once
#include <string>

class RestHandler
{
public:
    std::string Get(const char*url);
    std::string Put(const char*url);
};
