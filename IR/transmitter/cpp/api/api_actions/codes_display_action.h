#pragma once
#include "api_action.h"
#include "../../codes/ir_codes_repository.h"
#include "../formatters/code_display_formatter.h"

class CodesDisplayAction : public ApiAction
{
	IIrCodesRepository& codeRepository;
	ICodeDisplayFormatter& codeDisplayFormatter;

	virtual std::string Action();

public:
	CodesDisplayAction(IIrCodesRepository& codeRepository,
		ICodeDisplayFormatter& codeDisplayFormatter)
		: codeRepository(codeRepository),
		codeDisplayFormatter(codeDisplayFormatter){}
};
