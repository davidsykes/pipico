#include <memory>
#include <vector>
#include "PicoScopeTests.h"
#include "../../pico_scope/pico_scope.h"
#include "../Mocks/MockHardwareInteface.h"

class MockHardwareInterface : public IMockHardwareInterface
{
	std::vector<int> values;
	std::vector<int> value_times;
	int next_value_index = 0;
	int next_value_time = 0;

	virtual uint64_t get_time_us();
	virtual int get_pins();
    virtual int wait_pins_change(sPinsChangeData* pinsChangeData, int mask, uint64_t timeout);

public:
	void Initialise(std::vector<int> values, std::vector<int> value_times);
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
	hw_if.Initialise({11, 42, 51, 63, 77}, {1, 5, 11, 23, 45});
	PicoScope scope(hw_if, 1000);

	PicoScopeTrace trace = scope.FetchTrace();

	AssertEqual(11, trace.initial_value);
	AssertEqual(4, trace.values.size());
	AssertEqual(4, trace.value_times.size());
	AssertEqual(42, trace.values[0]);
	AssertEqual(0, trace.value_times[0]);
	AssertEqual(51, trace.values[1]);
	AssertEqual(6, trace.value_times[1]);
	AssertEqual(63, trace.values[2]);
	AssertEqual(18, trace.value_times[2]);
	AssertEqual(77, trace.values[3]);
	AssertEqual(40, trace.value_times[3]);
}

static void OnlyTheMostRecentTraceIsRetained()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();
	PicoScope scope(hw_if, 1000);

	hw_if.Initialise({ 11, 42, 51, 63, 77 }, { 1, 5, 11, 23, 45 });
	PicoScopeTrace trace = scope.FetchTrace();
	hw_if.Initialise({ 111, 142, 151, 163, 177 }, { 1, 5, 11, 23, 45 });
	trace = scope.FetchTrace();

	AssertEqual(111, trace.initial_value);
	AssertEqual(4, trace.values.size());
	AssertEqual(4, trace.value_times.size());
	AssertEqual(142, trace.values[0]);
	AssertEqual(0, trace.value_times[0]);
	AssertEqual(151, trace.values[1]);
	AssertEqual(6, trace.value_times[1]);
	AssertEqual(163, trace.values[2]);
	AssertEqual(18, trace.value_times[2]);
	AssertEqual(177, trace.values[3]);
	AssertEqual(40, trace.value_times[3]);
}

static void ATimeOutReturnsAPartialTrace()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();
	hw_if.Initialise({ 11, 42, 51, 63, 77 }, { 1, 5, 11, 23, 45000 });
	PicoScope scope(hw_if, 1000);

	PicoScopeTrace trace = scope.FetchTrace();

	AssertEqual(11, trace.initial_value);
	AssertEqual(3, trace.values.size());
	AssertEqual(3, trace.value_times.size());
	AssertEqual(42, trace.values[0]);
	AssertEqual(0, trace.value_times[0]);
	AssertEqual(51, trace.values[1]);
	AssertEqual(6, trace.value_times[1]);
	AssertEqual(63, trace.values[2]);
	AssertEqual(18, trace.value_times[2]);
}

void PicoScopeTests::RunTests()
{
	ASimpleTraceCanBeCaptured();
	OnlyTheMostRecentTraceIsRetained();
	ATimeOutReturnsAPartialTrace();
}

void PicoScopeTests::CleanUpAfterTests()
{
	hardwareInterface.release();
}

void MockHardwareInterface::Initialise(std::vector<int> values, std::vector<int> value_times)
{
	this->values = values;
	this->value_times = value_times;
	next_value_index = 0;
}

uint64_t MockHardwareInterface::get_time_us()
{
	return next_value_time;
}


int MockHardwareInterface::get_pins()
{
	if (next_value_index < values.size())
	{
		int next_value = values[next_value_index];
		next_value_time = value_times[next_value_index];
		++next_value_index;
		return next_value;
	}
	next_value_time += 1000000;
	return values.back();

}

int MockHardwareInterface::wait_pins_change(sPinsChangeData* pinsChangeData, int mask, uint64_t timeout)
{
	while (true)
	{
		int pins_value = get_pins() + 999;
		if ((next_value_time - pinsChangeData->time_us) > timeout)
		{
			return 0;
		}
		if (pins_value != pinsChangeData->current_value)
		{
			pinsChangeData->new_value = pins_value;
			pinsChangeData->time_us = next_value_time;
			return 1;
		}
	}
}
