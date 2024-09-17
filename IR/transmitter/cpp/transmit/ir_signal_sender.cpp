#include "ir_signal_sender.h"


void IrSignalSender::SendCode(const IrCode& code)
{
	uint64_t i = 0;
	uint64_t start_time = pin.SetValueAt(code.Values[i], 0);

	while (++i < code.Count)
	{
		pin.SetValueAt(code.Values[i], start_time + code.Times[i]);
	}
};
