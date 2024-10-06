#include "code_sequence_repository.h"

CodeSequence SequenceNotFoundSequence("NullSequence", "Sequence Not Found");

CodeSequenceRepository::CodeSequenceRepository(IMessageLogger& messageLogger) : messageLogger(messageLogger)
{
	CreateSequence("Forward30", "Forward 30")
		.AddCode("SonyForward");

	CreateSequence("Forward30x2", "Forward 30 x 2")
		.AddCode("SonyForward")
		.AddCode("Pause")
		.AddCode("SonyForward");

	CreateSequence("SamsungVolumeUpx2", "Volume Up x 2")
		.AddCode("SamsungVolumeUp")
		.AddCode("Pause")
		.AddCode("SamsungVolumeUp");
}

const std::vector<CodeSequence>& CodeSequenceRepository::GetCodeSequences()
{
    return codeSequences;
}

const CodeSequence& CodeSequenceRepository::GetSequence(const std::string& name)
{
	for (int i = 0; i < codeSequences.size(); ++i)
	{
		if (name == codeSequences[i].Name)
		{
			return codeSequences[i];
		}
	}

	messageLogger.Log("Sequence '" + name + "' not found.");
    return SequenceNotFoundSequence;
}

CodeSequence& CodeSequenceRepository::CreateSequence(const char* name, const char* displayName)
{
	CodeSequence s(name, displayName);
	codeSequences.push_back(s);
	return codeSequences.back();
}