#include "ir_code_sender.h"


void IrCodeSender::SendCode(const IrCode& code)
{
	std::vector<int> times;
	times.reserve(code.Values.size());

	uint64_t i = 0;
	uint64_t start_time = pin.SetValueAt(code.Values[i], 0);

	times.push_back(start_time);

	while (++i < code.Count)
	{
		times.push_back(pin.SetValueAt(code.Values[i], start_time + code.Times[i]));
	}

	for (int x = 0 ; x < times.size() ; ++x)
	{
		printf("%d | %d | %d\n", code.Times[x], times[x], times[x] - times[0]);
	}
};
