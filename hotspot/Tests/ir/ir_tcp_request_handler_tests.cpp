#include <memory>
#include "ir_tcp_request_handler_tests.h"
#include "../../ir/ir_tcp_request_handler.h"


static std::unique_ptr<IrRedTcpRequestHandler> objectUnderTest;

static IrRedTcpRequestHandler& CreateObjectUnderTest()
{
	//mockRestHandler.reset(new MockRestHandler());
	objectUnderTest.reset(new IrRedTcpRequestHandler());
	return *objectUnderTest.get();
}

static void TheIrTcpRequestHandlerReturnsTheSumOfTheCodesDisplayHandlerAndTheCodesRecordHandler()
{
	TcpServer& tcp = CreateObjectUnderTest();
	std::string response = tcp.process_request("", "");

	AssertEqual("0", response);
}

void IrTcpRequestHandlerTests::RunTests()
{
	TheIrTcpRequestHandlerReturnsTheSumOfTheCodesDisplayHandlerAndTheCodesRecordHandler();
}

void IrTcpRequestHandlerTests::CleanUpAfterTests()
{
	//mockRestHandler.release();
	objectUnderTest.release();
}
