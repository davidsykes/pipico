#include <memory>
#include "codes_record_request_handler_tests.h"
#include "../../ir/server_responses/codes_record_request_handler.h"

static std::unique_ptr<CodesRecordRequestHandler> objectUnderTest;

static ICodesRecordRequestHandler& CreateObjectUnderTest()
{
	objectUnderTest.reset(new CodesRecordRequestHandler());
	return *objectUnderTest.get();
}

static void AnEmptyRequestReturnsARecordButton()
{
	ICodesRecordRequestHandler& handler = CreateObjectUnderTest();
	std::string response = handler.HandleRequest("");

	AssertEqual("<form action=\"/record\"><input type = \"submit\" value = \"Record\" /></form>", response);
}

void CodesRecordHandlerTests::RunTests()
{
	AnEmptyRequestReturnsARecordButton();
}

void CodesRecordHandlerTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}
