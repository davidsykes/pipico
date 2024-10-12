#include <memory>
#include "ir_controller_http_request_router_tests.h"
#include "../Mocks/MockApiAction.h"
#include "../../api/ir_controller_http_request_router.h"

static std::unique_ptr<MockApiAction> mockHomeRequestHandler;
static std::unique_ptr<MockApiAction> mockRawRequestHandler;
static std::unique_ptr<MockApiAction> mockPlayCodeRequestHandler;
static std::unique_ptr<MockApiAction> mockPlaySequenceRequestHandler;
static std::unique_ptr<IrControllerHttpRequestRouter> objectUnderTest;

static IrControllerHttpRequestRouter& CreateObjectUnderTest()
{
	mockHomeRequestHandler.reset(new MockApiAction("Home"));
	mockRawRequestHandler.reset(new MockApiAction("Raw"));
	mockPlayCodeRequestHandler.reset(new MockApiAction("Play Code"));
	mockPlaySequenceRequestHandler.reset(new MockApiAction("Play Sequence"));
	objectUnderTest.reset(new IrControllerHttpRequestRouter(
		*mockHomeRequestHandler.get(),
		*mockRawRequestHandler.get(),
		*mockPlayCodeRequestHandler.get(),
		*mockPlaySequenceRequestHandler.get()));
	return *objectUnderTest.get();
}

static void ARootRequestPassesTheRequestToTheHomeHandler()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET / bla");

	AssertEqual("Home", result);
}

static void ARawRequestPassesTheRequestToTheRawHandler()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /raw bla");

	AssertEqual("Raw", result);
}

static void FaviconRequestReturnsNotFound()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /favicon");

	AssertTrue(result.empty());
}

static void TheRecordRequestHasBeenRemoved()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /record");

	AssertEqual("", result);
}

static void ASendCodeRequestPassesTheCodeNameToTheIrPlayer()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /sendcode/code_name");

	AssertEqual("Play Code code_name", result);
}

static void ASendCodeRequestTerminatesTheCodeNameAtWhiteSpace()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /sendcode/code name");

	AssertEqual("Play Code code", result);
}

static void ASequenceRequestPassesTheSequenceNameToThePlaySequenceAction()
{
	IHttpRequestRouter& router = CreateObjectUnderTest();

	std::string result = router.RouteHttpRequest("GET /sequence/sequence_name");

	AssertEqual("Play Sequence sequence_name", result);
}

void IrControllerHttpRequestRouterTests::RunTests()
{
	ARootRequestPassesTheRequestToTheHomeHandler();
	ARawRequestPassesTheRequestToTheRawHandler();
	FaviconRequestReturnsNotFound();
	TheRecordRequestHasBeenRemoved();
	ASendCodeRequestPassesTheCodeNameToTheIrPlayer();
	ASendCodeRequestTerminatesTheCodeNameAtWhiteSpace();
	ASequenceRequestPassesTheSequenceNameToThePlaySequenceAction();
}

void IrControllerHttpRequestRouterTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockHomeRequestHandler.release();
	mockPlayCodeRequestHandler.release();
	mockPlaySequenceRequestHandler.release();
}
