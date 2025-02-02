#pragma once
#include <string>

class IRenderer
{
public:
	virtual std::string Render() { return ""; }
	virtual std::string Render(const std::string& parameters) { return ""; }
};
