#include <memory>
#include <vector>
#include "PicoScopeTests.h"
#include "../../pico_scope/pico_scope.h"
#include "../Mocks/MockHardwareInteface.h"

const int trace_pin = 17;

class MockHardwareInterface : public IMockHardwareInterface
{
public:
	int initial_value = 0;
	std::vector<int> timings;
};

static std::unique_ptr<MockHardwareInterface> hardwareInterface;


static MockHardwareInterface& CreateHardwareInterface()
{
	hardwareInterface.reset(new MockHardwareInterface());
	return *hardwareInterface.get();
}

static void ASimpleTraceCanBeCaptured()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();
	hw_if.initial_value = 0;
	hw_if.timings = { 1, 5, 11, 23 };
	PicoScope scope(hw_if);

	PicoScopeTrace trace = scope.FetchTrace(trace_pin);

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