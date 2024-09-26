#pragma once
#include "api_action.h"
#include "../../codes/ir_codes_repository.h"
#include "../../transmit/ir_signal_sender.h"

class PlayIrAction : public ApiAction
{
	IIrCodesRepository& codesRepository;
	IIrSignalSender& irSignalSender;
	ApiAction& actionWhenFinished;

	virtual std::string Action(const std::string& p);

public:
	PlayIrAction(IIrSignalSender& irSignalSender,
		IIrCodesRepository& codesRepository,
		ApiAction& actionWhenFinished)
		: irSignalSender(irSignalSender),
		codesRepository(codesRepository),
		actionWhenFinished(actionWhenFinished) {}
};
