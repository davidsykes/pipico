#pragma once
#include "../codes/ir_codes_repository.h"
#include "../gpio/gpio.h"

class IIrCodeSender
{
public:
	virtual void SendCode(const IrCode& code) = 0;
};

class IrCodeSender : public IIrCodeSender
{
	IGPIOOutputPin& pin;
	virtual void SendCode(const IrCode& code);
public:
	IrCodeSender(IGPIOOutputPin& pin)
		: pin(pin) {}
};
