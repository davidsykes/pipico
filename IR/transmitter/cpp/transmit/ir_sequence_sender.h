#pragma once
#include "ir_code_sender.h"
#include "../codes/ir_codes_repository.h"
#include "../codes/code_sequence.h"

class IIrSequenceSender
{
public:
	virtual void SendSequence(const CodeSequence& code) = 0;
};

class IrSequenceSender : public IIrSequenceSender
{
	IIrCodeSender& codeSender;

	virtual void SendSequence(const CodeSequence& code);
public:
	IrSequenceSender(IIrCodeSender& codeSender)
		: codeSender(codeSender) {}
};
