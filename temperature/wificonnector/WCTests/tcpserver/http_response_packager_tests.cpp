#include <memory>
#include "http_response_packager_tests.h"
#include "../Mocks/MockHttpRequestRouter.h"
#include "../../src/tcpserver/http_response_packager.h"

static std::unique_ptr<MockRequestRouter> mockInputFormRenderer;
static std::unique_ptr<HttpResponsePackager> objectUnderTest;

static HttpResponsePackager& CreateObjectUnderTest()
{
	mockInputFormRenderer.reset(new MockRequestRouter("Router result"));
	objectUnderTest.reset(new HttpResponsePackager(*mockInputFormRenderer.get()));
	return *objectUnderTest.get();
}

static void RequestsArePassedToTheRouterAndPackagedWithHtmlMarkers()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	std::string header, body;

	int result = packager.RouteRequestAndPackageResponse("/ bla", header, body);

	AssertEqual(1, result);

	AssertEqual("<!DOCTYPE html><html><head><style type=\"text/css\">button { font-size:100px; }</style></head><body>Router result</body></html> ", body);
}

static void TheHeaderIsTerminatedByTwoCRLF()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	std::string header, body;

	int result = packager.RouteRequestAndPackageResponse("/ bla", header, body);

	AssertEqual(1, result);
	AssertEqual("HTTP/1.1 200 OK\r\nContent-Length: 126\r\nContent-Type : text/html; charset=utf-8\r\nConnection: close\r\n\r\n", header);
}

static void TheHeaderIsCreatedWithTheCorrectContentLength()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	mockInputFormRenderer.get()->SetResponse("a much longer response");
	std::string header, body;

	int result = packager.RouteRequestAndPackageResponse("/favicon", header, body);

	AssertEqual(1, result);
	AssertEqual("HTTP/1.1 200 OK\r\nContent-Length: 135\r\nContent-Type : text/html; charset=utf-8\r\nConnection: close\r\n\r\n", header);
}

static void IfTheRouterDoesNotRouteThen404IsReturned()
{
	IHttpResponsePackager& packager = CreateObjectUnderTest();
	mockInputFormRenderer.get()->SetResponse("");
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
	mockInputFormRenderer.release();
}
