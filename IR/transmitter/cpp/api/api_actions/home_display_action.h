#pragma once
#include "api_action.h"
#include "../../codes/code_sequence_repository.h"
#include "../formatters/button_formatter.h"

class HomeDisplayAction : public ApiAction
{
	CodeSequenceRepository& codeSequenceRepository;
	IButtonFormatter& buttonFormatter;

	virtual std::string Action();

public:
	HomeDisplayAction(CodeSequenceRepository& codeSequenceRepository,
		IButtonFormatter& buttonFormatter) : codeSequenceRepository(codeSequenceRepository), buttonFormatter(buttonFormatter) {}
};
