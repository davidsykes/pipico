#pragma once
#include <string>

class IPercentDecoder
{
public:
	virtual std::string Decode(const std::string& value) = 0;
};
