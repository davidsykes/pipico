#pragma once
#include "../../codes/ir_code.h"

class ICodeDisplayFormatter
{
public:
	virtual std::string FormatCode(const IrCode& code) = 0;
};

class CodeDisplayFormatter : public ICodeDisplayFormatter
{
	std::string ip_address;

	virtual std::string FormatCode(const IrCode& code);

public:
	CodeDisplayFormatter(const std::string& ip_address) : ip_address(ip_address) {}
};
