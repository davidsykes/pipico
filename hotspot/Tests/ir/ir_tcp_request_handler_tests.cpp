#include <memory>
#include "ir_tcp_request_handler_tests.h"
#include "../../ir/ir_tcp_request_handler.h"

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
static std::unique_ptr<IrRedTcpRequestHandler> objectUnderTest;

static IrRedTcpRequestHandler& CreateObjectUnderTest()
{
	mockCodesDisplayRequestHandler.reset(new MockCodesDisplayRequestHandler());
	mockCodesRecordRequestHandler.reset(new MockCodesRecordRequestHandler());
	objectUnderTest.reset(new IrRedTcpRequestHandler(*mockCodesDisplayRequestHandler.get(),*mockCodesRecordRequestHandler.get()));
	return *objectUnderTest.get();
}

static void TheIrTcpRequestHandlerReturnsTheSumOfTheCodesDisplayHandlerAndTheCodesRecordHandler()
{
	TcpServer& tcp = CreateObjectUnderTest();
	std::string response = tcp.process_request("", "");

	AssertEqual("codes displaycodes record", response);
}

void IrTcpRequestHandlerTests::RunTests()
{
	TheIrTcpRequestHandlerReturnsTheSumOfTheCodesDisplayHandlerAndTheCodesRecordHandler();
}

void IrTcpRequestHandlerTests::CleanUpAfterTests()
{
	mockCodesDisplayRequestHandler.release();
	mockCodesRecordRequestHandler.release();
	objectUnderTest.release();
}
