#include <memory>
#include "http_request_router_tests.h"
#include "../Mocks/MockApiAction.h"
#include "../../api/http_request_router.h"

static std::unique_ptr<MockApiAction> mockHomeRequestHandler;
static std::unique_ptr<MockApiAction> mockRecordRequestHandler;
static std::unique_ptr<MockApiAction> mockPlayCodeRequestHandler;
static std::unique_ptr<HttpRequestRouter> objectUnderTest;

static HttpRequestRouter& CreateObjectUnderTest()
{
	mockHomeRequestHandler.reset(new MockApiAction("Home"));
	mockRecordRequestHandler.reset(new MockApiAction("Record"));
	mockPlayCodeRequestHandler.reset(new MockApiAction("Play"));
	objectUnderTest.reset(new HttpRequestRouter(
		*mockHomeRequestHandler.get(),
		*mockRecordRequestHandler.get(),
		*mockPlayCodeRequestHandler.get()));
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

static void ARecordRequestPassesTheRequestToTheRecordHander()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /record");

	AssertEqual("Record", result);
}

static void ASendCodeRequestPassesTheRequestToTheIrPlayer()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /sendcode/code_name");

	AssertEqual("Play code_name", result);
}

static void ASendCodeRequestTerminatesTheCodeNameAtWhiteSpace()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /sendcode/code name");

	AssertEqual("Play code", result);
}

void HttpRequestRouterTests::RunTests()
{
	ARootRequestPassesTheRequestToTheHomeHandler();
	FaviconRequestReturnsNotFound();
	ARecordRequestPassesTheRequestToTheRecordHander();
	ASendCodeRequestPassesTheRequestToTheIrPlayer();
	ASendCodeRequestTerminatesTheCodeNameAtWhiteSpace();
}

void HttpRequestRouterTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockHomeRequestHandler.release();
	mockRecordRequestHandler.release();
	mockPlayCodeRequestHandler.release();
}
