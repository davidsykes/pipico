#include "play_ir_sequence_action.h"


std::string PlayIrSequenceAction::Action(const std::string& name)
{
	const CodeSequence& sequence = codeSequenceRepository.GetSequence(name);

	irSequenceSender.SendSequence(sequence);

	return actionWhenFinished.Action();
}