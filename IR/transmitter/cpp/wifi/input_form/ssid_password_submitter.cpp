#include "ssid_password_submitter.h"

std::string SSIDPasswordSubmitter::Render(const std::string& parameters)
{
	std::string remainder = parameters;
	std::vector<FlashParameter> flashParameters;

	size_t ampersand = remainder.find('&');

	while (ampersand != std::string::npos)
	{
		AddParameter(flashParameters, remainder.substr(0, ampersand));
		remainder = remainder.substr(ampersand+1);
		ampersand = remainder.find('&');
	}
	AddParameter(flashParameters, remainder);

	if (flashParameters.size() > 0)
	{
		flashWriter.WriteParameters(flashParameters);

		return "Ok";
	}

	return "Fail";
}


void SSIDPasswordSubmitter::AddParameter(std::vector<FlashParameter>& flashParameters, const std::string& data)
{
	size_t eq = data.find('=');
	if (eq != std::string::npos)
	{
		std::string name = data.substr(0, eq);
		std::string value = percentDecoder.Decode(data.substr(eq + 1));
		FlashParameter p(name, value);
		flashParameters.push_back(p);
	}
}
