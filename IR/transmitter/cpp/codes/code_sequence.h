#pragma once
#include <string>
#include <vector>

class CodeSequence
{
public:
	std::string Name;
	std::vector<std::string> Codes;

	CodeSequence(const std::string& name) : Name(name) {}
	CodeSequence(const char* name) : Name(name) {}
};
