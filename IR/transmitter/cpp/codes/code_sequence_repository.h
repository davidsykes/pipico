#pragma once
#include <vector>
#include "code_sequence.h"
#include "../tools/message_logger.h"

class ICodeSequenceRepository
{
public:
	virtual const std::vector<CodeSequence>& GetCodeSequences() = 0;
	virtual const CodeSequence& GetSequence(const std::string& name) = 0;
};

class CodeSequenceRepository : public ICodeSequenceRepository
{
	IMessageLogger& messageLogger;
	std::vector<CodeSequence> codeSequences;

	virtual const std::vector<CodeSequence>& GetCodeSequences();
	virtual const CodeSequence& GetSequence(const std::string& name);

	CodeSequence& CreateSequence(const char* name, const char* displayName);
public:
	CodeSequenceRepository(IMessageLogger& messageLogger);

	void AddSequence(const CodeSequence& cs) { codeSequences.push_back(cs); }
};
