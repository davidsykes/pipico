#include <memory>
#include "http_request_router_tests.h"
#include "../../ir/server/http_request_router.h"

class MockRequestHandler : public IHttpRequestHandler
{
	std::string requestType;

	virtual std::string HandleHttpRequest(const char* request) { return requestType; };

public:
	MockRequestHandler(const char* type) : requestType(type) {}
};

static std::unique_ptr<MockRequestHandler> mockHomeRequestHandler;
static std::unique_ptr<HttpRequestRouter> objectUnderTest;

static HttpRequestRouter& CreateObjectUnderTest()
{
	mockHomeRequestHandler.reset(new MockRequestHandler("Home"));
	objectUnderTest.reset(new HttpRequestRouter(*mockHomeRequestHandler.get()));
	return *objectUnderTest.get();
}

static void ARootRequestPassesTheRequestToTheHomeHandler()
{
	IHttpRequestHandler& router = CreateObjectUnderTest();

	std::string result = router.HandleHttpRequest("/ bla");

	AssertEqual("Home", result);
}

static void FaviconRequestReturnsNotFound()
{
	IHttpRequestHandler& router = CreateObjectUnderTest();

	std::string result = router.HandleHttpRequest("/favicon");

	AssertTrue(result.empty());
}

void HttpRequestRouterTests::RunTests()
{
	ARootRequestPassesTheRequestToTheHomeHandler();
	FaviconRequestReturnsNotFound();
}

void HttpRequestRouterTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}
