#include <memory>
#include "http_request_router_tests.h"
#include "../Mocks/MockApiAction.h"
#include "../../api/http_request_router.h"

static std::unique_ptr<MockApiAction> mockHomeRequestHandler;
static std::unique_ptr<MockApiAction> mockRawRequestHandler;
static std::unique_ptr<MockApiAction> mockPlayCodeRequestHandler;
static std::unique_ptr<HttpRequestRouter> objectUnderTest;

static HttpRequestRouter& CreateObjectUnderTest()
{
	mockHomeRequestHandler.reset(new MockApiAction("Home"));
	mockRawRequestHandler.reset(new MockApiAction("Raw"));
	mockPlayCodeRequestHandler.reset(new MockApiAction("Play"));
	objectUnderTest.reset(new HttpRequestRouter(
		*mockHomeRequestHandler.get(),
		*mockRawRequestHandler.get(),
		*mockPlayCodeRequestHandler.get()));
	return *objectUnderTest.get();
}

static void ARootRequestPassesTheRequestToTheHomeHandler()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET / bla");

	AssertEqual("Home", result);
}

static void ARawRequestPassesTheRequestToTheRawHandler()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /raw bla");

	AssertEqual("Raw", result);
}

static void FaviconRequestReturnsNotFound()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /favicon");

	AssertTrue(result.empty());
}

static void TheRecordRequestHasBeenRemoved()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /record");

	AssertEqual("", result);
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
	ARawRequestPassesTheRequestToTheRawHandler();
	FaviconRequestReturnsNotFound();
	TheRecordRequestHasBeenRemoved();
	ASendCodeRequestPassesTheRequestToTheIrPlayer();
	ASendCodeRequestTerminatesTheCodeNameAtWhiteSpace();
}

void HttpRequestRouterTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockHomeRequestHandler.release();
	mockPlayCodeRequestHandler.release();
}
