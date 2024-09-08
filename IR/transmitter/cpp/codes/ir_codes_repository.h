#pragma once
#include <vector>
#include "ir_code.h"

class IIrCodesRepository
{
public:
	virtual IrCode First() = 0;
};



class IrCodesRepository : public IIrCodesRepository
{
	std::vector<IrCode> codes;

	virtual IrCode First();

public:
	IrCodesRepository();
};

