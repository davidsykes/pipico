#pragma once
#include "api_action.h"
#include "../../codes/code_sequence_repository.h"
#include "../../transmit/ir_sequence_sender.h"

class PlayIrSequenceAction : public ApiAction
{
	ICodeSequenceRepository& codeSequenceRepository;
	IIrSequenceSender& irSequenceSender;
	ApiAction& actionWhenFinished;

	virtual std::string Action(const std::string& p);

public:
	PlayIrSequenceAction(IIrSequenceSender& irSequenceSender,
		ICodeSequenceRepository& codeSequenceRepository,
		ApiAction& actionWhenFinished)
		: irSequenceSender(irSequenceSender),
		codeSequenceRepository(codeSequenceRepository),
		actionWhenFinished(actionWhenFinished) {}
};
