#include <memory>
#include "http_request_router_tests.h"
#include "../Mocks/MockApiAction.h"
#include "../../api/http_request_router.h"

static std::unique_ptr<MockApiAction> mockHomeRequestHandler;
static std::unique_ptr<MockApiAction> mockRecordRequestHandler;
static std::unique_ptr<HttpRequestRouter> objectUnderTest;

static HttpRequestRouter& CreateObjectUnderTest()
{
	mockHomeRequestHandler.reset(new MockApiAction("Home"));
	mockRecordRequestHandler.reset(new MockApiAction("Record"));
	objectUnderTest.reset(new HttpRequestRouter(
		*mockHomeRequestHandler.get(),
		*mockRecordRequestHandler.get()));
	return *objectUnderTest.get();
}

static void ARootRequestPassesTheRequestToTheHomeHandler()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET / bla");

	AssertEqual("Home", result);
}

static void FaviconRequestReturnsNotFound()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /favicon");

	AssertTrue(result.empty());
}

static void ARecordRequestPassedTheRequestToTheRecordHander()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /record");

	AssertEqual("Record", result);
}

void HttpRequestRouterTests::RunTests()
{
	ARootRequestPassesTheRequestToTheHomeHandler();
	FaviconRequestReturnsNotFound();
	ARecordRequestPassedTheRequestToTheRecordHander();
}

void HttpRequestRouterTests::CleanUpAfterTests()
{
	mockHomeRequestHandler.release();
	mockRecordRequestHandler.release();
	objectUnderTest.release();
}
