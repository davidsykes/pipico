#include <memory>
#include "GPIOTests.h"
#include "../../gpio/gpio.h"
#include "../Mocks/MockHardwareInteface.h"

namespace
{
	class MockHardwareInterface : public IMockHardwareInterface
	{
		virtual void initialise_input_pin(int pin_number) { initialised_input_pin_number = pin_number; }
		virtual void initialise_output_pin(int pin_number) { initialised_output_pin_number = pin_number; }
		virtual int gpio_get(int pin_number) { return pin_value; }
		virtual void gpio_set_pull_up(int pin_number, int value);
		virtual void gpio_put(int pin_number, bool value) { pin_value = value; }
	public:
		int initialised_input_pin_number = 0;
		int initialised_output_pin_number = 0;
		int pin_value = 0;
		int pull_up_value_for_initialised_pin = 0;
	};
}

static std::unique_ptr<MockHardwareInterface> hardwareInterface;


static MockHardwareInterface& CreateHardwareInterface()
{
	hardwareInterface.reset(new MockHardwareInterface);
	return *hardwareInterface.get();
}

static void GPIOInputPinInitialisesTheInputPin()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();

	GPIOInputPin ip(5, hw_if);

	AssertEqual(5, hw_if.initialised_input_pin_number);
}

static void GPIOInputPinReturnsHardwareValues()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();
	GPIOInputPin ip(5, hw_if);

	hw_if.pin_value = 1;
	bool value = ip.Value();
	AssertTrue(value);

	hw_if.pin_value = 0;
	value = ip.Value();
	AssertFalse(value);
}

static void SetPullUpCallsHardwareSetPullUp()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();
	GPIOInputPin ip(5, hw_if);
	ip.SetPullUp(1);

	AssertEqual(1, hw_if.pull_up_value_for_initialised_pin);

}

static void GPIOOutputPinInitialisesTheOutputPin()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();

	GPIOOutputPin ip(5, hw_if);

	AssertEqual(5, hw_if.initialised_output_pin_number);
}

static void GPIOOutputPinSetsHardwareValues()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();

	GPIOOutputPin ip(5, hw_if);
	ip.SetValue(47);

	AssertEqual(1, hw_if.pin_value);
}

void GPIOTests::RunTests()
{
	GPIOInputPinInitialisesTheInputPin();
	GPIOInputPinReturnsHardwareValues();
	SetPullUpCallsHardwareSetPullUp();
	GPIOOutputPinInitialisesTheOutputPin();
	GPIOOutputPinSetsHardwareValues();
}

void MockHardwareInterface::gpio_set_pull_up(int pin_number, int value)
{
	if (pin_number == initialised_input_pin_number)
	{
		pull_up_value_for_initialised_pin = value;
	}
}

void GPIOTests::CleanUpAfterTests()
{
	hardwareInterface.release();
}