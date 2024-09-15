#pragma once
#include "api_action.h"
#include "../../codes/ir_codes_repository.h"
#include "../../transmit/ir_signal_sender.h"

class PlayIrAction : public ApiAction
{
	IIrCodesRepository& codesRepository;
	IIrSignalSender& irSignalSender;

	virtual std::string Action(const std::string& p);

public:
	PlayIrAction(IIrSignalSender& irSignalSender,
		IIrCodesRepository& codesRepository)
		: irSignalSender(irSignalSender),
		codesRepository(codesRepository){}
};
