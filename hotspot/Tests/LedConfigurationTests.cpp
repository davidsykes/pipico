#include "Assert.h"
#include "LedConfigurationTests.h"
#include "..\configurations\led_configuration.h"


void LedConfigurationTests::RunTests()
{
	LedConfiguration* config = new LedConfiguration();

	std::string result = config->process_request("request", "params");

	std::string expected = "<html><body><h1>Hello from Pico W.</h1><p>Led is OFF</p><p><a href=\"?led=1\">Turn led ON</a></body></html>";
	AssertEqual(result, expected);
}