#include <memory>
#include "PicoScopeCaptureAndPostTests.h"
#include "../../pico_scope/pico_scope_capture_and_post.h"
#include "../../rest/rest_handler.h"
#include "../Mocks/MockHardwareInteface.h"

namespace
{
	class MockHardwareInterface : public IMockHardwareInterface
	{
		virtual void set_led(bool value) { LedState = value; }
	public:
		bool LedState = false;
	};
}

class MockPicoScope : public IPicoScope
{
	MockHardwareInterface& hw_if;
	PicoScopeTrace& trace;
	virtual PicoScopeTrace& FetchTrace();
public:
	MockPicoScope(MockHardwareInterface& hw_if, PicoScopeTrace& trace) : hw_if(hw_if), trace(trace) {}
	bool LedStateDuringCapture = false;
};

class MockRestHandler : public IRestHandler
{
	MockHardwareInterface& hw_if;

	virtual std::string Get(const char* url) { Assert("Invalid"); }
	virtual std::string Put(const char* url, const char* body);
public:
	MockRestHandler(MockHardwareInterface& hw_if) : hw_if(hw_if) {}

	std::string PutUrl;
	std::string PutData;
	bool LedStateDuringPost = true;
};

static std::unique_ptr<PicoScopeCaptureAndPost> objectUnderTest;
static std::unique_ptr<MockPicoScope> mockPicoScope;
static std::unique_ptr<MockHardwareInterface> mockHardwareInterface;
static std::unique_ptr<TraceDataFormatter> traceDataFormatter;
static std::unique_ptr<MockRestHandler> mockRestHandler;
static std::unique_ptr<PicoScopeTrace> capturedPicoScopeTrace;

static PicoScopeCaptureAndPost& CreateObjectUnderTest()
{
	capturedPicoScopeTrace.reset(new PicoScopeTrace);
	capturedPicoScopeTrace.get()->initial_value = 4242;
	mockHardwareInterface.reset(new MockHardwareInterface);
	traceDataFormatter.reset(new TraceDataFormatter);
	mockPicoScope.reset(new MockPicoScope(*mockHardwareInterface.get(),*capturedPicoScopeTrace.get()));
	mockRestHandler.reset(new MockRestHandler(*mockHardwareInterface.get()));
	objectUnderTest.reset(new PicoScopeCaptureAndPost(
		*mockHardwareInterface.get(),
		*mockPicoScope.get(),
		*traceDataFormatter.get(),
		*mockRestHandler.get(),
		"trace url"));
	return *objectUnderTest.get();
}

static void ATraceIsCapturedWhileTheHardwareLightIsOn()
{
	IPicoScopeCaptureAndPost& cap = CreateObjectUnderTest();

	cap.CaptureAndPost();

	AssertTrue(mockPicoScope.get()->LedStateDuringCapture);
}

static void TheTraceIsPostedWhileTheHardwareLightIsOff()
{
	IPicoScopeCaptureAndPost& cap = CreateObjectUnderTest();

	cap.CaptureAndPost();

	AssertEqual("trace url", mockRestHandler.get()->PutUrl);
	AssertEqual("{\"InitialValue\":4242,\"Values\":[]}", mockRestHandler.get()->PutData);
	AssertFalse(mockRestHandler.get()->LedStateDuringPost);
}

PicoScopeTrace& MockPicoScope::FetchTrace()
{
	LedStateDuringCapture = hw_if.LedState;
	return trace;
}

std::string MockRestHandler::Put(const char* url, const char* body)
{
	LedStateDuringPost = hw_if.LedState;
	PutUrl = url;
	PutData = body;
	return "";
}

void PicoScopeCaptureAndPostTests::RunTests()
{
	ATraceIsCapturedWhileTheHardwareLightIsOn();
	TheTraceIsPostedWhileTheHardwareLightIsOff();
}

void PicoScopeCaptureAndPostTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockRestHandler.release();
	mockPicoScope.release();
	mockHardwareInterface.release();
	capturedPicoScopeTrace.release();
}
