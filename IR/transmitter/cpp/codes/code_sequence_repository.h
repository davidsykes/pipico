#pragma once
#include "code_sequence.h"
#include <vector>

class ICodeSequenceRepository
{
public:
	virtual const std::vector<CodeSequence>& GetCodeSequences() = 0;
};

class CodeSequenceRepository : public ICodeSequenceRepository
{
	std::vector<CodeSequence> codeSequences;

	virtual const std::vector<CodeSequence>& GetCodeSequences();
public:
	CodeSequenceRepository();

	void AddSequence(const CodeSequence& cs) { codeSequences.push_back(cs); }
	const CodeSequence& GetSequence(const std::string& name);
};
