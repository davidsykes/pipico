#pragma once
#include "api_action.h"
#include "../../codes/ir_codes_repository.h"
#include "../../transmit/ir_code_sender.h"

class PlayIrCodeAction : public ApiAction
{
	IIrCodesRepository& codesRepository;
	IIrCodeSender& irCodeSender;
	ApiAction& actionWhenFinished;

	virtual std::string Action(const std::string& p);

public:
	PlayIrCodeAction(IIrCodeSender& irCodeSender,
		IIrCodesRepository& codesRepository,
		ApiAction& actionWhenFinished)
		: irCodeSender(irCodeSender),
		codesRepository(codesRepository),
		actionWhenFinished(actionWhenFinished) {}
};
