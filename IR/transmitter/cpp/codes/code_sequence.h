#pragma once
#include <string>
#include <vector>

class CodeSequence
{
public:
	std::string Name;
	std::string DisplayText;
	std::vector<std::string> Codes;

	CodeSequence(const std::string& name, const std::string& display_text) : Name(name), DisplayText(display_text) {}
};
