#include "Assert.h"
#include "HotSpotConfigurationTests.h"
#include "..\configurations\hotspot_configuration.h"
#include "MockHtmlRenderer.h"

void HotSpotConfigurationTests::RunTests()
{
	IHtmlRenderer* renderer = new MockHtmlRenderer();
	Configuration* config = new HotSpotConfiguration("hellow", renderer);

	std::string result = config->process_request("request", "params");

	AssertEqual(result, "html(body(h1(hellow)p(Enter Wifi Details)))");
}