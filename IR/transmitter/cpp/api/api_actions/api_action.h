#pragma once
#include <string>

class ApiAction
{
public:
	virtual std::string Action() { return ""; }
	virtual std::string Action(const std::string&) { return ""; }
};