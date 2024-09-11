#include <sstream>
#include "codes_display_action.h"


std::string CodesDisplayAction::Action()
{
	std::vector<IrCode>& codes = codeRepository.GetCodes();

	std::ostringstream str;

	for (int i = 0 ; i < codes.size() ; ++i)
	{
		str << codeDisplayFormatter.FormatCode(codes[i]) << "<br>";
	}

	return str.str();
}