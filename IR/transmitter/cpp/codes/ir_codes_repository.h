#pragma once
#include <vector>
#include <exception>
#include "ir_code.h"

class IIrCodesRepository
{
public:
	virtual std::vector<IrCode>& GetCodes() = 0;
	virtual IrCode& GetCode(const std::string& name) = 0;

	class InvalidCodeException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Invalid Code";
		}
	};
};


class IrCodesRepository : public IIrCodesRepository
{
	std::vector<IrCode> codes;

	virtual std::vector<IrCode>& GetCodes() { return codes; }
	virtual IrCode& GetCode(const std::string& name);

public:
	IrCodesRepository();
};

