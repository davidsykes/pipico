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

class MockLogsDisplayWidget : public IWidget
{
	virtual std::string RenderWidget() { return "logs"; }
};

static std::unique_ptr<ICodesDisplayRequestHandler> mockCodesDisplayRequestHandler;
static std::unique_ptr<ICodesRecordRequestHandler> mockCodesRecordRequestHandler;
static std::unique_ptr<MockLogsDisplayWidget> mockLogsDisplayWidget;
static std::unique_ptr<HttpServerHomePage> objectUnderTest;

static HttpServerHomePage& CreateObjectUnderTest()
{
	mockCodesDisplayRequestHandler.reset(new MockCodesDisplayRequestHandler());
	mockCodesRecordRequestHandler.reset(new MockCodesRecordRequestHandler());
	mockLogsDisplayWidget.reset(new MockLogsDisplayWidget());
	objectUnderTest.reset(new HttpServerHomePage(
		*mockCodesDisplayRequestHandler.get(),
		*mockCodesRecordRequestHandler.get(),
		*mockLogsDisplayWidget.get()));
	return *objectUnderTest.get();
}

static void HomePageShowsCodesCommandAndLogs()
{
	IHttpRequestHandler& home = CreateObjectUnderTest();
	std::string response = home.ProcessHttpRequest("");

	AssertEqual("codes display<br><br>codes record<br><br>logs", response);
}

void HttpServerHomePageTests::RunTests()
{
	HomePageShowsCodesCommandAndLogs();
}

void HttpServerHomePageTests::CleanUpAfterTests()
{
	mockCodesDisplayRequestHandler.release();
	mockCodesRecordRequestHandler.release();
	mockLogsDisplayWidget.release();
	objectUnderTest.release();
}
