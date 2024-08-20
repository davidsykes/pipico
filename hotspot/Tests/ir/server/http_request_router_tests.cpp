#include <memory>
#include "http_request_router_tests.h"
#include "../../ir/server/http_request_router.h"

class MockRequestHandler : public IHttpRequestHandler
{
	std::string requestType;

	virtual std::string ProcessHttpRequest(const char* request) { return requestType; };

public:
	MockRequestHandler(const char* type) : requestType(type) {}
};

static std::unique_ptr<MockRequestHandler> mockHomeRequestHandler;
static std::unique_ptr<MockRequestHandler> mockRecordRequestHandler;
static std::unique_ptr<HttpRequestRouter> objectUnderTest;

static HttpRequestRouter& CreateObjectUnderTest()
{
	mockHomeRequestHandler.reset(new MockRequestHandler("Home"));
	mockRecordRequestHandler.reset(new MockRequestHandler("Record"));
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
	objectUnderTest.release();
	mockHomeRequestHandler.release();
	mockRecordRequestHandler.release();
}
