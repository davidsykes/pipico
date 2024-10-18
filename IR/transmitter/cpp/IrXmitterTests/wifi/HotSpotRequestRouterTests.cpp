#include <memory>
#include "TestFramework.h"
#include "HotSpotRequestRouterTests.h"
#include "../Mocks/MockRenderer.h"
#include "../../wifi/hotspot_request_router.h"

static std::unique_ptr<HotSpotRequestRouter> objectUnderTest;
static std::unique_ptr<MockRenderer> mockInputFormRenderer;
static std::unique_ptr<MockRenderer> mockHotspotSubmitRenderer;

static HotSpotRequestRouter* CreateTestObject()
{
	mockInputFormRenderer.reset(new MockRenderer("ssid"));
	mockHotspotSubmitRenderer.reset(new MockRenderer("hotspotsubmit"));
	objectUnderTest.reset(new HotSpotRequestRouter(
		*mockInputFormRenderer.get(),
		*mockHotspotSubmitRenderer.get()));
	return objectUnderTest.get();
}

static void RootRequestsAreRoutedToTheSsidPasswordInputForm()
{
	IHttpRequestRouter* router = CreateTestObject();

	std::string html = router->RouteHttpRequest("/");

	AssertEqual("ssid", html);
}

static void GoogleSafeBrowsingReturnsAnEmptyObject()
{
	IHttpRequestRouter* router = CreateTestObject();

	std::string html = router->RouteHttpRequest("CONNECT proxy-safebrowsing");

	AssertEqual("{}", html);
}

static void EnteredDetailsArePassedToTheFlashWriter()
{
	IHttpRequestRouter* router = CreateTestObject();

	std::string html = router->RouteHttpRequest("GET /hotspotsubmit?ssid=a907&password=pwd HTTP/1.1");

	AssertEqual("hotspotsubmit ssid=a907&password=pwd HTTP/1.1", html);
}

void HotSpotRequestRouterTests::RunTests()
{
	RootRequestsAreRoutedToTheSsidPasswordInputForm();
	GoogleSafeBrowsingReturnsAnEmptyObject();
	EnteredDetailsArePassedToTheFlashWriter();
}

void HotSpotRequestRouterTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockInputFormRenderer.release();
	mockHotspotSubmitRenderer.release();
}