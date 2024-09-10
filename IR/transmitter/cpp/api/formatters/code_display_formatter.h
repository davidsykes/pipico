#pragma once

class ICodeDisplayFormatter
{
public:
	virtual std::string FormatCode(const IrCode& code) = 0;
};

class CodeDisplayFormatter : public ICodeDisplayFormatter
{
	virtual std::string FormatCode(const IrCode& code) { return "Not Implemented"; }
};
