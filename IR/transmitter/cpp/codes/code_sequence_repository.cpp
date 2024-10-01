#include "code_sequence_repository.h"

#define NUMBER_OF_SEQUENCES 3

const char* FastForward30Codes[] = { "SonyForward", 0 };
const char* SamsungVolumeDownCodes[] = { "SamsungVolumeDown", 0 };
const char* TestSequenceCodes[] = { "testcode", 0 };


const char* sequenceNames[NUMBER_OF_SEQUENCES] = { "FastForward30", "SamsungVolumeDown", "Test"};
const char* displayNames[NUMBER_OF_SEQUENCES] = { "Forward 30", "Volume Down", "Test"};
const char** sequences[NUMBER_OF_SEQUENCES] = { FastForward30Codes, SamsungVolumeDownCodes, TestSequenceCodes };

CodeSequenceRepository::CodeSequenceRepository()
{
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

    return codeSequences[0];
}