#pragma once
#include "../codes/ir_codes_repository.h"


class IIrSignalSender
{
public:
	virtual void SendCode(const IrCode& code) = 0;
};