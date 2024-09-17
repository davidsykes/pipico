#pragma once
#include "../codes/ir_codes_repository.h"
#include "../hw_if/ihardware_interface.h"

class IIrSignalSender
{
public:
	virtual void SendCode(const IrCode& code) = 0;
};

class IrSignalSender : public IIrSignalSender
{
	IHardwareInterface& hw;
	int pin_number;
	virtual void SendCode(const IrCode& code);
public:
	IrSignalSender(IHardwareInterface& hw,
		int pin_number)
		: hw(hw),
		pin_number(pin_number) {}
};
