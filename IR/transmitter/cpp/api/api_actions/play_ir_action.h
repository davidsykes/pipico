#pragma once
#include "api_action.h"
#include "../../codes/ir_code.h"
#include "../../transmit/ir_signal_sender.h"

class PlayIrAction : public ApiAction
{
	IIrSignalSender& irSignalSender;

	virtual std::string Action(const std::string& p);

public:
	PlayIrAction(IIrSignalSender& irSignalSender) : irSignalSender(irSignalSender) {}
};
