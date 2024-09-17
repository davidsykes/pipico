#pragma once
#include "../codes/ir_codes_repository.h"
#include "../gpio/gpio.h"

class IIrSignalSender
{
public:
	virtual void SendCode(const IrCode& code) = 0;
};

class IrSignalSender : public IIrSignalSender
{
	IGPIOOutputPin& pin;
	virtual void SendCode(const IrCode& code);
public:
	IrSignalSender(IGPIOOutputPin& pin)
		: pin(pin) {}
};
