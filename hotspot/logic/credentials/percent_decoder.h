#pragma once
#include <string>

class IPercentDecoder
{
public:
	virtual std::string Decode(const std::string& value) = 0;
};


class PercentDecoder : public IPercentDecoder
{
	virtual std::string Decode(const std::string& value);
};