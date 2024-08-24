#include <memory>
#include "http_response_packager_tests.h"
#include "../../ir/server/ihttp_request_router.h"
#include "../../ir/server/http_response_packager.h"

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

static void RequestsArePassedToTheRouter()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	std::string header, body;

	int result = packager.RouteRequestAndPackageResponse("/ bla", header, body);

	AssertEqual(1, result);
	AssertEqual("Router result", body);
}

static void TheHeaderIsTerminatedByTwoCRLF()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	std::string header, body;

	int result = packager.RouteRequestAndPackageResponse("/ bla", header, body);

	AssertEqual(1, result);
	AssertEqual("HTTP/1.1 200 OK\r\nContent-Length: 13\r\nContent-Type : text/plain; charset=utf-8\r\n\r\n", header);
}

static void TheHeaderIsCreatedWithTheCorrectContentLength()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	mockRequestRouter.get()->SetResponse("a much longer response");
	std::string header, body;

	int result = packager.RouteRequestAndPackageResponse("/favicon", header, body);

	AssertEqual(1, result);
	AssertEqual("HTTP/1.1 200 OK\r\nContent-Length: 22\r\nContent-Type : text/plain; charset=utf-8\r\n\r\n", header);
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
	RequestsArePassedToTheRouter();
	TheHeaderIsTerminatedByTwoCRLF();
	TheHeaderIsCreatedWithTheCorrectContentLength();
	IfTheRouterDoesNotRouteThen404IsReturned();
}

void HttpResponsePackagerTests::CleanUpAfterTests()
{
	mockRequestRouter.release();
	objectUnderTest.release();
}
