#pragma once
#include "../hw_if/ihardware_interface.h"

class IBlinker
{
public:
	virtual void Blink(int count) = 0;
};

class Blinker : public IBlinker
{
	IHardwareInterface& hw_if;

	virtual void Blink(int count);

public:
	Blinker(IHardwareInterface& hw_if) : hw_if(hw_if) {}
};
