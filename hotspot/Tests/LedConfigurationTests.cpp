#include "LedConfigurationTests.h"
#include "..\configurations\led_configuration.h"


void LedConfigurationTests::RunTests()
{
	LedConfiguration* config = new LedConfiguration();

	std::string result = config->process_request("request", "params");
}