#include <memory>
#include "TestFramework.h"
#include "HotSpotRequestRouterTests.h"
#include "../Mocks/MockRenderer.h"
#include "../../wifi/hotspot_request_router.h"

static std::unique_ptr<HotSpotRequestRouter> objectUnderTest;
static std::unique_ptr<MockRenderer> mockInputFormRenderer;

static HotSpotRequestRouter* CreateTestObject()
{
	mockInputFormRenderer.reset(new MockRenderer("ssid"));
	objectUnderTest.reset(new HotSpotRequestRouter(*mockInputFormRenderer.get()));
	return objectUnderTest.get();
}

static void RootRequestsAreRoutedToTheSsidPasswordInputForm()
{
	IHttpRequestRouter* router = CreateTestObject();

	std::string html = router->RouteHttpRequest("/");

	AssertEqual("ssid", html);
}

void HotSpotRequestRouterTests::RunTests()
{
	RootRequestsAreRoutedToTheSsidPasswordInputForm();
}

void HotSpotRequestRouterTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockInputFormRenderer.release();
}