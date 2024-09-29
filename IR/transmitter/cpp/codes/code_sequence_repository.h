#pragma once
#include "code_sequence.h"
#include <vector>

class ICodeSequenceRepository
{
public:
	virtual const std::vector<CodeSequence>& GetCodeSequences() = 0;
	virtual const CodeSequence& GetSequence(const std::string& name) = 0;
};

class CodeSequenceRepository : public ICodeSequenceRepository
{
	std::vector<CodeSequence> codeSequences;

	virtual const std::vector<CodeSequence>& GetCodeSequences();
	virtual const CodeSequence& GetSequence(const std::string& name);
public:
	CodeSequenceRepository();

	void AddSequence(const CodeSequence& cs) { codeSequences.push_back(cs); }
};
