#pragma once
#include "code_sequence.h"
#include <vector>

class CodeSequenceRepository
{
	std::vector<CodeSequence> codeSequences;
public:
	void AddSequence(const CodeSequence& cs) { codeSequences.push_back(cs); }
	std::vector<CodeSequence>& GetCodeSequences();
};
