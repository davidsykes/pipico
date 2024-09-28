#include <memory>
#include "http_response_packager_tests.h"
#include "../../tcp_server/http_response_packager.h"
#include "../../api/http_request_router.h"

class MockRequestRouter : public IHttpRequestRouter
{
	std::string requestType;

	virtual std::string RouteHttpRequest(const char* request) { return requestType; };

public:
	MockRequestRouter(const char* type) : requestType(type) {}

	void SetResponse(const char* response) { requestType = response; }
};

static std::unique_ptr<MockRequestRouter> mockRequestRouter;
static std::unique_ptr<HttpResponsePackager> objectUnderTest;

static HttpResponsePackager& CreateObjectUnderTest()
{
	mockRequestRouter.reset(new MockRequestRouter("Router result"));
	objectUnderTest.reset(new HttpResponsePackager(*mockRequestRouter.get()));
	return *objectUnderTest.get();
}

static void RequestsArePassedToTheRouterAndPackagedWithHtmlMarkers()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	std::string header, body;

	int result = packager.RouteRequestAndPackageResponse("/ bla", header, body);

	AssertEqual(1, result);

	AssertEqual("<!DOCTYPE html><html><body>Router result</body></html> ", body);
}

static void TheHeaderIsTerminatedByTwoCRLF()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	std::string header, body;

	int result = packager.RouteRequestAndPackageResponse("/ bla", header, body);

	AssertEqual(1, result);
	AssertEqual("HTTP/1.1 200 OK\r\nContent-Length: 55\r\nContent-Type : text/plain; charset=utf-8\r\n\r\n", header);
}

static void TheHeaderIsCreatedWithTheCorrectContentLength()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	mockRequestRouter.get()->SetResponse("a much longer response");
	std::string header, body;

	int result = packager.RouteRequestAndPackageResponse("/favicon", header, body);

	AssertEqual(1, result);
	AssertEqual("HTTP/1.1 200 OK\r\nContent-Length: 64\r\nContent-Type : text/plain; charset=utf-8\r\n\r\n", header);
}

static void IfTheRouterDoesNotRouteThen404IsReturned()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	mockRequestRouter.get()->SetResponse("");
	std::string header, body;

	int result = packager.RouteRequestAndPackageResponse("/favicon", header, body);

	AssertEqual(0, result);
}

void HttpResponsePackagerTests::RunTests()
{
	RequestsArePassedToTheRouterAndPackagedWithHtmlMarkers();
	TheHeaderIsTerminatedByTwoCRLF();
	TheHeaderIsCreatedWithTheCorrectContentLength();
	IfTheRouterDoesNotRouteThen404IsReturned();
}

void HttpResponsePackagerTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockRequestRouter.release();
}
