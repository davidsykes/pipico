#pragma once
#include <vector>
#include "ir_code.h"
#include "../tools/message_logger.h"

class IIrCodesRepository
{
public:
	virtual std::vector<IrCode>& GetCodes() = 0;
	virtual IrCode* GetCode(const std::string& name) = 0;
};


class IrCodesRepository : public IIrCodesRepository
{
	IMessageLogger& messageLogger;

	std::vector<IrCode> codes;

	virtual std::vector<IrCode>& GetCodes() { return codes; }
	virtual IrCode* GetCode(const std::string& name);

public:
	IrCodesRepository(IMessageLogger& messageLogger);
};

