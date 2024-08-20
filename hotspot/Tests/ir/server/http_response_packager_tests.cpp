#include <memory>
#include "http_response_packager_tests.h"
#include "../../ir/server/http_response_packager.h"

class MockRequestHandler : public IHttpRequestHandler
{
	std::string requestType;

	virtual std::string HandleHttpRequest(const char* request) { return requestType; };

public:
	MockRequestHandler(const char* type) : requestType(type) {}

	void SetResponse(const char* response) { requestType = response; }
};

static std::unique_ptr<MockRequestHandler> mockRequestHandler;
static std::unique_ptr<HttpResponsePackager> objectUnderTest;

static HttpResponsePackager& CreateObjectUnderTest()
{
	mockRequestHandler.reset(new MockRequestHandler("Router result"));
	objectUnderTest.reset(new HttpResponsePackager(*mockRequestHandler.get()));
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
	mockRequestHandler.get()->SetResponse("a much longer response");
	std::string header, body;

	int result = packager.RouteRequestAndPackageResponse("/favicon", header, body);

	AssertEqual(1, result);
	AssertEqual("HTTP/1.1 200 OK\r\nContent-Length: 22\r\nContent-Type : text/plain; charset=utf-8\r\n\r\n", header);
}

static void IfTheRouterDoesNotRouteThen404IsReturned()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	mockRequestHandler.get()->SetResponse("");
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
	objectUnderTest.release();
	mockRequestHandler.release();
}
