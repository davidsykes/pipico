#pragma once
#include <string>

class IButtonFormatter
{
public:
	virtual std::string FormatButton(const std::string& text, const std::string& link) = 0;
};

class ButtonFormatter : public IButtonFormatter
{
	virtual std::string FormatButton(const std::string& text, const std::string& link);
};