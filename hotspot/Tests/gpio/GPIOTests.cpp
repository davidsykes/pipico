#include <memory>
#include "GPIOTests.h"
#include "../../gpio/gpio.h"
#include "../Mocks/MockHardwareInteface.h"

namespace
{
	class MockHardwareInterface : public IMockHardwareInterface
	{
		virtual void initialise_input_pin(int pin_number) { initialised_pin_number = pin_number; }
		virtual int gpio_get(int pin_number) { return pin_value; }
	public:
		int initialised_pin_number = 0;
		int pin_value = 0;
	};
}

static std::unique_ptr<MockHardwareInterface> hardwareInterface;


MockHardwareInterface& CreateHardwareInterface()
{
	hardwareInterface.reset(new MockHardwareInterface());
	return *hardwareInterface.get();
}

void GPIOInputPinInitialisesTheInputPin()
{
	MockHardwareInterface& hw_if = CreateHardwareInterface();

	GPIOInputPin ip(5, hw_if);

	AssertEqual(5, hw_if.initialised_pin_number);
}

void GPIOInputPinReturnsHardwareValues()
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


void GPIOTests::RunTests()
{
	GPIOInputPinInitialisesTheInputPin();
	GPIOInputPinReturnsHardwareValues();
	SetPullUpCallsHardwareSetPullUp();
}



void GPIOTests::CleanUpAfterTests()
{
	hardwareInterface.release();
}