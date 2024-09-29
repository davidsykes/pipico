#include "play_ir_code_action.h"


std::string PlayIrCodeAction::Action(const std::string& code_name)
{
	IrCode* code = codesRepository.GetCode(code_name);

	if (code == 0)
	{
		return std::string("Code ") + code_name + " not found";
	}

	irCodeSender.SendCode(*code);

	return actionWhenFinished.Action();
}