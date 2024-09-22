#include <memory>
#include <vector>
#include "BlinkerTests.h"
#include "../../tools/blinker.h"
#include "../Mocks/MockHardwareInteface.h"

namespace
{
	class MockHardwareInterface : public IMockHardwareInterface
	{
		int time = 0;
		virtual void set_led(bool value);
		virtual void sleep_us(int useconds) { time += useconds;  }
	public:
		std::vector<int> times;
		std::vector<int> values;
	};
}

static std::unique_ptr<Blinker> objectUnderTest;
static std::unique_ptr<MockHardwareInterface> mockHardwareInterface;

static Blinker& CreateTestObject()
{
	mockHardwareInterface.reset(new MockHardwareInterface);
	objectUnderTest.reset(new Blinker(*mockHardwareInterface.get()));
	return *objectUnderTest.get();
}

static void BlinkOnce()
{
	IBlinker& blinker = CreateTestObject();

	blinker.Blink(1);

	MockHardwareInterface& hw_if = *mockHardwareInterface.get();
	AssertEqual(2, hw_if.times.size());
	AssertEqual(2, hw_if.values.size());
	AssertEqual(0, hw_if.times[0]);
	AssertEqual(1, hw_if.values[0]);
	AssertEqual(200000, hw_if.times[1]);
	AssertEqual(0, hw_if.values[1]);
}

static void Blink3Times()
{
	IBlinker& blinker = CreateTestObject();

	blinker.Blink(3);

	MockHardwareInterface& hw_if = *mockHardwareInterface.get();
	AssertEqual(6, hw_if.times.size());
	AssertEqual(6, hw_if.values.size());
	AssertEqual(0, hw_if.times[0]);
	AssertEqual(1, hw_if.values[0]);
	AssertEqual(200000, hw_if.times[1]);
	AssertEqual(0, hw_if.values[1]);
	AssertEqual(400000, hw_if.times[2]);
	AssertEqual(1, hw_if.values[2]);
	AssertEqual(600000, hw_if.times[3]);
	AssertEqual(0, hw_if.values[3]);
	AssertEqual(800000, hw_if.times[4]);
	AssertEqual(1, hw_if.values[4]);
	AssertEqual(1000000, hw_if.times[5]);
	AssertEqual(0, hw_if.values[5]);
}

void MockHardwareInterface::set_led(bool value)
{
	times.push_back(time);
	values.push_back(value);
}

void BlinkerTests::RunTests()
{
	BlinkOnce();
	Blink3Times();
}

void BlinkerTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockHardwareInterface.release();
}
