#include <memory>
#include "http_server_record_handler_tests.h"
#include "../../../ir/server/http_server_record_handler.h"
#include "../../../pico_scope/pico_scope_record_and_post.h"

class MockPicoScopeRecordAndPost : public IPicoScopeRecordAndPost
{
	virtual std::string RecordAndPostTrace() { return "R&P"; }
};

static std::unique_ptr<MockPicoScopeRecordAndPost> mockPicoScopeRecordAndPost;
static std::unique_ptr<HttpServerRecordHandler> objectUnderTest;

static HttpServerRecordHandler& CreateObjectUnderTest()
{
	mockPicoScopeRecordAndPost.reset(new MockPicoScopeRecordAndPost());
	objectUnderTest.reset(new HttpServerRecordHandler(*mockPicoScopeRecordAndPost.get()));
	return *objectUnderTest.get();
}

static void TheHandlerCallsTheIrScopeRecorder()
{
	IHttpRequestHandler& handler = CreateObjectUnderTest();
	std::string response = handler.ProcessHttpRequest("");

	AssertEqual("R&P", response);
}

void HttpServerRecordHandlerTests::RunTests()
{
	TheHandlerCallsTheIrScopeRecorder();
}

void HttpServerRecordHandlerTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockPicoScopeRecordAndPost.release();
}
