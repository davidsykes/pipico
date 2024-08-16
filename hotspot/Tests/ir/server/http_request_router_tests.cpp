#include <memory>
#include "http_request_router_tests.h"
#include "../../ir/server/http_request_router.h"

class MockRequestHandler : public IHttpRequestHandler
{
	std::string requestType;

	virtual int HandleHttpRequest(const char* request, std::string& header, std::string& body) { body = requestType; return 1; };

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
	IHttpRequestRouter& router = CreateObjectUnderTest();
	std::string header, body;

	int result = router.HandleHttpRequest("/ bla", header, body);

	AssertEqual(1, result);
	AssertEqual("Home", body);
}

static void FaviconRequestReturnsNotFound()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();
	std::string header, body;

	int result = router.HandleHttpRequest("/favicon", header, body);

	AssertEqual(0, result);
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
