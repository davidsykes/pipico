#include <memory>
#include "TestFramework.h"
#include "LedConfigurationTests.h"
#include "..\configurations\led_configuration.h"

static std::unique_ptr<LedConfiguration> config;

static Configuration* CreateTestObject()
{
	config.reset(new LedConfiguration);
	return config.get();
}

void LedConfigurationTests::RunTests()
{
	Configuration* config = CreateTestObject();

	std::string result = config->process_request("request", "params");

	std::string expected = "<html><body><h1>Hello from Pico W.</h1><p>Led is OFF</p><p><a href=\"?led=1\">Turn led ON</a></body></html>";
	AssertEqual(result, expected);
}


void LedConfigurationTests::CleanUpAfterTests()
{
	config.release();
}