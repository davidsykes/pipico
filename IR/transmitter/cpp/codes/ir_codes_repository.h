#pragma once
#include <vector>
#include "ir_code.h"

class IIrCodesRepository
{
public:
	virtual std::vector<IrCode>& GetCodes() = 0;
};



class IrCodesRepository : public IIrCodesRepository
{
	std::vector<IrCode> codes;

	virtual std::vector<IrCode>& GetCodes() { return codes; }

public:
	IrCodesRepository();
};

