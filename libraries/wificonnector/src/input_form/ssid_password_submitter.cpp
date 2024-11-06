#include "ssid_password_submitter.h"

std::string GetDataUpToTheFirstWhitespace(std::string data);

std::string SSIDPasswordSubmitter::Render(const std::string& parameters)
{
	std::string data = GetDataUpToTheFirstWhitespace(parameters);
	std::vector<FlashParameter> flashParameters;

	size_t ampersand = data.find('&');

	while (ampersand != std::string::npos)
	{
		AddParameter(flashParameters, data.substr(0, ampersand));
		data = data.substr(ampersand+1);
		ampersand = data.find('&');
	}
	AddParameter(flashParameters, data);

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

std::string GetDataUpToTheFirstWhitespace(std::string data)
{
	size_t space = data.find(' ');
	return data.substr(0, space);
}