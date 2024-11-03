#pragma once
#include <string>

class FlashParameter
{
public:
	std::string Name;
	std::string Value;

	FlashParameter(const std::string& name, const std::string& value) : Name(name), Value(value) {}
};
