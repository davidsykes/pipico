#include <memory>
#include "PicoScopeTests.h"
#include "../../pico_scope/pico_scope.h"
#include "../Mocks/MockHardwareInteface.h"

class MockHardwareInterface : public IMockHardwareInterface
{
};

static std::unique_ptr<MockHardwareInterface> hardwareInterface;


static MockHardwareInterface& CreateHardwareInterface()
{
	hardwareInterface.reset(new MockHardwareInterface());
	return *hardwareInterface.get();
}

void ASimpleTraceCanBeCaptured()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();
	PicoScope scope(hw_if);

	PicoScopeTrace trace = scope.FetchTrace();

	AssertEqual("5", trace.gethtml());
}

void PicoScopeTests::RunTests()
{
	ASimpleTraceCanBeCaptured();
}



void PicoScopeTests::CleanUpAfterTests()
{
	hardwareInterface.release();
}