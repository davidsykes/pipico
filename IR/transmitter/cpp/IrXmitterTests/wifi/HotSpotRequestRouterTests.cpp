#include <memory>
#include "TestFramework.h"
#include "HotSpotRequestRouterTests.h"
#include "../Mocks/MockHttpRequestRouter.h"
#include "../../wifi/hotspot_request_router.h"

static std::unique_ptr<HotSpotRequestRouter> objectUnderTest;
static std::unique_ptr<MockRequestRouter> mockRequestRouter;

static HotSpotRequestRouter* CreateTestObject()
{
	mockRequestRouter.reset(new MockRequestRouter("ssid"));
	objectUnderTest.reset(new HotSpotRequestRouter(*mockRequestRouter.get()));
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
	mockRequestRouter.release();
}