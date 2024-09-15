#include "play_ir_action.h"


std::string PlayIrAction::Action(const std::string& code_name)
{
	try
	{
		IrCode& code = codesRepository.GetCode(code_name);

		irSignalSender.SendCode(code);
	}
	catch (IIrCodesRepository::InvalidCodeException exception)
	{
		return std::string("Code ") + code_name + " not found";
	}

	return "";
}