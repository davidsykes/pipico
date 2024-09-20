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
	virtual std::string Get(const char* url) { Assert("Invalid"); }
	virtual std::string Put(const char* url, const char* body) { Assert("Invalid"); }
public:
	bool TraceWasPosted = false;
};

static std::unique_ptr<PicoScopeCaptureAndPost> objectUnderTest;
static std::unique_ptr<MockPicoScope> mockPicoScope;
static std::unique_ptr<MockHardwareInterface> mockHardwareInterface;
static std::unique_ptr<MockRestHandler> mockRestHandler;
static std::unique_ptr<PicoScopeTrace> capturedPicoScopeTrace;

static PicoScopeCaptureAndPost& CreateObjectUnderTest()
{
	capturedPicoScopeTrace.reset(new PicoScopeTrace);
	mockHardwareInterface.reset(new MockHardwareInterface);
	mockPicoScope.reset(new MockPicoScope(*mockHardwareInterface.get(), *capturedPicoScopeTrace.get()));
	mockRestHandler.reset(new MockRestHandler);
	objectUnderTest.reset(new PicoScopeCaptureAndPost(*mockHardwareInterface.get(), *mockPicoScope.get()));
	return *objectUnderTest.get();
}

static void ATraceIsCapturedWhileTheHardwareLightIsOn()
{
	IPicoScopeCaptureAndPost& cap = CreateObjectUnderTest();

	cap.CaptureAndPost();

	AssertTrue(mockPicoScope.get()->LedStateDuringCapture);
}

static void ATraceCanBeCapturedFormattedAndPosted()
{
	IPicoScopeCaptureAndPost& cap = CreateObjectUnderTest();

	cap.CaptureAndPost();

	AssertTrue(mockRestHandler.get()->TraceWasPosted);
}

PicoScopeTrace& MockPicoScope::FetchTrace()
{
	LedStateDuringCapture = hw_if.LedState;
	return trace;
}

void PicoScopeCaptureAndPostTests::RunTests()
{
	ATraceIsCapturedWhileTheHardwareLightIsOn();
	ATraceCanBeCapturedFormattedAndPosted();
}

void PicoScopeCaptureAndPostTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockRestHandler.release();
	mockPicoScope.release();
	mockHardwareInterface.release();
	capturedPicoScopeTrace.release();
}
