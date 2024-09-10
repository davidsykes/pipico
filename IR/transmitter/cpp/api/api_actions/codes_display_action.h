#pragma once
#include "iapi_action.h"
#include "../../codes/ir_codes_repository.h"
#include "../formatters/code_display_formatter.h"

class CodesDisplayAction : public IApiAction
{
	IIrCodesRepository& codeRepository;
	ICodeDisplayFormatter& codeDisplayFormatter;

	virtual std::string ApiAction();

public:
	CodesDisplayAction(IIrCodesRepository& codeRepository,
		ICodeDisplayFormatter& codeDisplayFormatter)
		: codeRepository(codeRepository),
		codeDisplayFormatter(codeDisplayFormatter){}
};
