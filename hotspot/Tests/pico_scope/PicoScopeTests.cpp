#include <memory>
#include <vector>
#include "PicoScopeTests.h"
#include "../../pico_scope/pico_scope.h"
#include "../Mocks/MockHardwareInteface.h"

const int trace_pin = 17;
const std::string pf = "{\"code\":\"code\",\"wavepoints\":[";

class MockHardwareInterface : public IMockHardwareInterface
{
	int pin_value = 0;
	std::vector<int> timings;
	int next_timing = 0;

	virtual int gpio_get(int pin_number) { return pin_value; }
	virtual uint64_t get_time_us();
	virtual uint64_t wait_value(int pin_number, int value, uint64_t timeout);

public:
	void Initialise(int value, std::vector<int> timings);
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
	hw_if.Initialise(0, { 1, 5, 11, 23 });
	PicoScope scope(hw_if, 1000);

	PicoScopeTrace trace = scope.FetchTrace(trace_pin);

	AssertEqual(1, trace.start_value);
	AssertEqual(3, trace.changes.size());
	AssertEqual(4, trace.changes[0]);
	AssertEqual(10, trace.changes[1]);
	AssertEqual(22, trace.changes[2]);
}

static void ATraceCanTriggerOnAFallingSignal()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();
	hw_if.Initialise(1, { 1, 5, 11, 23 });
	PicoScope scope(hw_if, 1000);

	PicoScopeTrace trace = scope.FetchTrace(trace_pin);

	AssertEqual(0, trace.start_value);
	AssertEqual(3, trace.changes.size());
	AssertEqual(4, trace.changes[0]);
	AssertEqual(10, trace.changes[1]);
	AssertEqual(22, trace.changes[2]);
}

static void OnlyTheMostRecentTraceIsRetained()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();
	PicoScope scope(hw_if, 1000);

	hw_if.Initialise(1, { 1, 5, 11, 23 });
	PicoScopeTrace trace = scope.FetchTrace(trace_pin);
	hw_if.Initialise(1, { 1, 15, 111, 123 });
	trace = scope.FetchTrace(trace_pin);

	AssertEqual(0, trace.start_value);
	AssertEqual(3, trace.changes.size());
	AssertEqual(14, trace.changes[0]);
	AssertEqual(110, trace.changes[1]);
	AssertEqual(122, trace.changes[2]);
}

static void ATimeOutReturnsAPartialTrace()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();
	hw_if.Initialise(1, { 1, 5, 11});
	PicoScope scope(hw_if, 1000);

	PicoScopeTrace trace = scope.FetchTrace(trace_pin);

	AssertEqual(0, trace.start_value);
	AssertEqual(2, trace.changes.size());
	AssertEqual(4, trace.changes[0]);
	AssertEqual(10, trace.changes[1]);
}

static void TimeoutWithoutValuesReturnsAnEmptyTrace()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();
	hw_if.Initialise(1, { 1 });
	PicoScope scope(hw_if, 1000);

	PicoScopeTrace trace = scope.FetchTrace(trace_pin);

	AssertEqual(0, trace.start_value);
	AssertEqual(0, trace.changes.size());
}

void PicoScopeTests::RunTests()
{
	ASimpleTraceCanBeCaptured();
	ATraceCanTriggerOnAFallingSignal();
	OnlyTheMostRecentTraceIsRetained();
	ATimeOutReturnsAPartialTrace();
	TimeoutWithoutValuesReturnsAnEmptyTrace();
}

void PicoScopeTests::CleanUpAfterTests()
{
	hardwareInterface.release();
}

void MockHardwareInterface::Initialise(int value, std::vector<int> timings)
{
	this->pin_value = value;
	this->timings = timings;
	next_timing = 0;
}

uint64_t MockHardwareInterface::get_time_us()
{
	if (next_timing < timings.size())
	{
		return timings[next_timing++];
	}
	return -1;
}

uint64_t MockHardwareInterface::wait_value(int pin_number, int value, uint64_t timeout)
{
	pin_value = GPIO_ON_VALUE - pin_value;
	if (pin_number == trace_pin && pin_value == value && next_timing < timings.size())
	{
		return timings[next_timing++];
	}
	return 0;
}
