#include <memory>
#include "HttpServerHomePageTests.h"
#include "../../../ir/server/pages/http_server_home_page.h"

class MockCodesDisplayRequestHandler : public ICodesDisplayRequestHandler
{
	virtual std::string HandleRequest(const std::string& request) { return "codes display"; }
};

class MockCodesRecordRequestHandler : public ICodesRecordRequestHandler
{
	virtual std::string HandleRequest(const std::string& request) { return "codes record"; }
};

static std::unique_ptr<ICodesDisplayRequestHandler> mockCodesDisplayRequestHandler;
static std::unique_ptr<ICodesRecordRequestHandler> mockCodesRecordRequestHandler;
static std::unique_ptr<HttpServerHomePage> objectUnderTest;

static HttpServerHomePage& CreateObjectUnderTest()
{
	mockCodesDisplayRequestHandler.reset(new MockCodesDisplayRequestHandler());
	mockCodesRecordRequestHandler.reset(new MockCodesRecordRequestHandler());
	objectUnderTest.reset(new HttpServerHomePage(*mockCodesDisplayRequestHandler.get(),*mockCodesRecordRequestHandler.get()));
	return *objectUnderTest.get();
}

static void TheHandlerReturnsTheSumOfTheCodesDisplayHandlerAndTheCodesRecordHandler()
{
	IHttpRequestHandler& handler = CreateObjectUnderTest();
	std::string response = handler.ProcessHttpRequest("");

	AssertEqual("codes display<br><br>codes record", response);
}

void HttpServerHomePageTests::RunTests()
{
	TheHandlerReturnsTheSumOfTheCodesDisplayHandlerAndTheCodesRecordHandler();
}

void HttpServerHomePageTests::CleanUpAfterTests()
{
	mockCodesDisplayRequestHandler.release();
	mockCodesRecordRequestHandler.release();
	objectUnderTest.release();
}
