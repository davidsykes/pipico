#include <memory>
#include "GPIOTests.h"
#include "../../gpio/gpio.h"
#include "../Mocks/MockHardwareInteface.h"

#define TEST_PIN_NUMBER 5

namespace
{
	class MockHardwareInterface : public IMockHardwareInterface
	{
		virtual void initialise_input_pin(int pin_number) { initialised_input_pin_number = pin_number; }
		virtual void initialise_output_pin(int pin_number) { initialised_output_pin_number = pin_number; }
		virtual int gpio_get(int pin_number) { return pin_value; }
		virtual void gpio_set_pull_up(int pin_number, int value);
		virtual void gpio_put(int pin_number, bool value) { pin_value = value; }
		virtual uint64_t gpio_put_at_us(int pin_number, bool value, uint64_t time_us);
	public:
		int initialised_input_pin_number = 0;
		int initialised_output_pin_number = 0;
		int pin_value = 0;
		int pull_up_value_for_initialised_pin = 0;
		uint64_t set_at_time = 0;
	};
}

static std::unique_ptr<MockHardwareInterface> hardwareInterface;
static std::unique_ptr<GPIOInputPin> gPIOInputPin;
static std::unique_ptr<GPIOOutputPin> gPIOOutputPin;

static MockHardwareInterface& CreateHardwareInterface2()
{
	hardwareInterface.reset(new MockHardwareInterface);
	return *hardwareInterface.get();
}

static GPIOInputPin& CreateTestInputPin()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface2();
	gPIOInputPin.reset(new GPIOInputPin(TEST_PIN_NUMBER, hw_if));
	return *gPIOInputPin.get();
}

static GPIOOutputPin& CreateTestOutputPin()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface2();
	gPIOOutputPin.reset(new GPIOOutputPin(TEST_PIN_NUMBER, hw_if));
	return *gPIOOutputPin.get();
}

static void GPIOInputPinInitialisesTheInputPin()
{
	GPIOInputPin& ip = CreateTestInputPin();

	AssertEqual(5, hardwareInterface.get()->initialised_input_pin_number);
}

static void GPIOInputPinReturnsHardwareValues()
{
	GPIOInputPin& ip = CreateTestInputPin();

	hardwareInterface.get()->pin_value = 1;
	bool value = ip.Value();
	AssertTrue(value);

	hardwareInterface.get()->pin_value = 0;
	value = ip.Value();
	AssertFalse(value);
}

static void SetPullUpCallsHardwareSetPullUp()
{
	GPIOInputPin& ip = CreateTestInputPin();

	ip.SetPullUp(1);

	AssertEqual(1, hardwareInterface.get()->pull_up_value_for_initialised_pin);

}

static void GPIOOutputPinInitialisesTheOutputPin()
{
	GPIOOutputPin& ip = CreateTestOutputPin();

	AssertEqual(5, hardwareInterface.get()->initialised_output_pin_number);
}

static void GPIOOutputPinSetsHardwareValues()
{
	GPIOOutputPin& ip = CreateTestOutputPin();

	ip.SetValue(1);

	AssertEqual(1, hardwareInterface.get()->pin_value);
}

static void GPIOOutputPinSetValueAtUsSetsValueAtTimeAndReturnsTime()
{
	GPIOOutputPin& ip = CreateTestOutputPin();

	uint64_t result = ip.SetValueAt(1, 1234);

	AssertEqual(1236, result);
	AssertEqual(1, hardwareInterface.get()->pin_value);
	AssertEqual(1234, hardwareInterface.get()->set_at_time);
}

void MockHardwareInterface::gpio_set_pull_up(int pin_number, int value)
{
	if (pin_number == initialised_input_pin_number)
	{
		pull_up_value_for_initialised_pin = value;
	}
}

uint64_t MockHardwareInterface::gpio_put_at_us(int pin_number, bool value, uint64_t time_us)
{
	if (pin_number == TEST_PIN_NUMBER)
	{
		pin_value = value;
		set_at_time = time_us;
		return time_us + 2;
	}
	return 123;
}

void GPIOTests::RunTests()
{
	GPIOInputPinInitialisesTheInputPin();
	GPIOInputPinReturnsHardwareValues();
	SetPullUpCallsHardwareSetPullUp();
	GPIOOutputPinInitialisesTheOutputPin();
	GPIOOutputPinSetsHardwareValues();
	GPIOOutputPinSetValueAtUsSetsValueAtTimeAndReturnsTime();
}

void GPIOTests::CleanUpAfterTests()
{
	gPIOInputPin.release();
	gPIOOutputPin.release();
	hardwareInterface.release();
}