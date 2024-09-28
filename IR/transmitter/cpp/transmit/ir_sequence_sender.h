#pragma once
#include "ir_code_sender.h"
#include "../codes/ir_codes_repository.h"
#include "../codes/code_sequence.h"

class IIrSequenceSender
{
public:
	virtual void SendSequence(const CodeSequence& sequence) = 0;
};

class IrSequenceSender : public IIrSequenceSender
{
	IIrCodesRepository& irCodesRepository;
	IIrCodeSender& codeSender;

	virtual void SendSequence(const CodeSequence& sequence);
public:
	IrSequenceSender(IIrCodesRepository& irCodesRepository, IIrCodeSender& codeSender)
		: irCodesRepository(irCodesRepository), codeSender(codeSender) {}
};
