#include "ir_signal_sender.h"


void IrSignalSender::SendCode(const IrCode& code)
{
	int i = 0;
	uint64_t start_time = hw.gpio_put_at_us(pin_number, code.Values[i], 0);

	while (++i < code.Count)
	{
		hw.gpio_put_at_us(pin_number, code.Values[i], start_time + code.Times[i]);
	}
};
