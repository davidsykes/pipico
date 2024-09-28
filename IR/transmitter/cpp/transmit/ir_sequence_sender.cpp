#include "ir_sequence_sender.h"


void IrSequenceSender::SendSequence(const CodeSequence& sequence)
{
	for (int c = 0; c < sequence.Codes.size(); ++c)
	{
		IrCode* code = irCodesRepository.GetCode(sequence.Codes[c]);
		codeSender.SendCode(*code);
	}
}