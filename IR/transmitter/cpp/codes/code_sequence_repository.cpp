#include "code_sequence_repository.h"

#define NUMBER_OF_SEQUENCES 4

const char* FastForward30Codes[] = { "SonyForward", 0 };
const char* FastForward30Codesx2[] = { "SonyForward", "Pause", "SonyForward" };
const char* SamsungVolumeDownCodes[] = { "SamsungVolumeDown", 0 };
const char* TestSequenceCodes[] = { "testcode", 0 };


const char* sequenceNames[NUMBER_OF_SEQUENCES] = { "FastForward30", "FastForward30x2", "SamsungVolumeDown", "Test"};
const char* displayNames[NUMBER_OF_SEQUENCES] = { "Forward 30", "Forward 30 x 2", "Volume Down", "Test"};
const char** sequences[NUMBER_OF_SEQUENCES] = { FastForward30Codes, FastForward30Codesx2, SamsungVolumeDownCodes, TestSequenceCodes };

CodeSequenceRepository::CodeSequenceRepository(IMessageLogger& messageLogger) : messageLogger(messageLogger)
{
	CodeSequence& sequence = CreateSequence("NullSequence", "Sequence Not Found");

	for (int i = 0; i < NUMBER_OF_SEQUENCES; ++i)
	{
		CodeSequence s(sequenceNames[i], displayNames[i]);
		const char** codes = sequences[i];
		while (codes[0])
		{
			s.Codes.push_back(codes[0]);
			++codes;
		}
		codeSequences.push_back(s);
	}
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
    return codeSequences[0];
}

CodeSequence& CodeSequenceRepository::CreateSequence(const char* name, const char* displayName)
{
	CodeSequence s(name, displayName);
	codeSequences.push_back(s);
	return codeSequences.back();
}