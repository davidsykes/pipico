#include "Assert.h"
#include "HotSpotConfigurationTests.h"
#include "..\configurations\hotspot_configuration.h"
#include "MockHtmlRenderer.h"
#include "MockInputFormRenderer.h"

void HotSpotConfigurationTests::RunTests()
{
	IHtmlRenderer* renderer = new MockHtmlRenderer();
	IInputFormRenderer* formRenderer = new MockInputFormRenderer();
	Configuration* config = new HotSpotConfiguration("hellow", renderer, formRenderer);

	std::string result = config->process_request("request", "params");

	AssertEqual(result, "html(body(h1(hellow)p(Enter Wifi Details){Form}))");
}