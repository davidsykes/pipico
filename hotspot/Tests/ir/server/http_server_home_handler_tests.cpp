#include <memory>
#include "http_server_home_handler_tests.h"
#include "../../../ir/server/http_server_home_handler.h"

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
static std::unique_ptr<HttpServerHomeHandler> objectUnderTest;

static HttpServerHomeHandler& CreateObjectUnderTest()
{
	mockCodesDisplayRequestHandler.reset(new MockCodesDisplayRequestHandler());
	mockCodesRecordRequestHandler.reset(new MockCodesRecordRequestHandler());
	objectUnderTest.reset(new HttpServerHomeHandler(*mockCodesDisplayRequestHandler.get(),*mockCodesRecordRequestHandler.get()));
	return *objectUnderTest.get();
}

static void TheHandlerReturnsTheSumOfTheCodesDisplayHandlerAndTheCodesRecordHandler()
{
	IHttpRequestHandler& handler = CreateObjectUnderTest();
	std::string response = handler.HandleHttpRequest("");

	AssertEqual("codes display<br><br>codes record", response);
}

void HttpServerHomeHandlerTests::RunTests()
{
	TheHandlerReturnsTheSumOfTheCodesDisplayHandlerAndTheCodesRecordHandler();
}

void HttpServerHomeHandlerTests::CleanUpAfterTests()
{
	mockCodesDisplayRequestHandler.release();
	mockCodesRecordRequestHandler.release();
	objectUnderTest.release();
}
