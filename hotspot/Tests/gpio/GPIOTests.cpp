#include <memory>
#include "GPIOTests.h"
#include "../../gpio/gpio.h"

class MockHardwareInterface : public IHardwareInterface
{
	virtual sHardwareInterface* raw_if() { return 0; }
	virtual void initialise_pico_stdio() {}
	virtual void initialise_input_pin(int pin_number) { initialised_pin_number = pin_number; }
	virtual void initialise_output_pin(int pin_number) {}
	virtual int gpio_get(int pin_number) { return pin_value; }
	virtual uint64_t wait_value(int pin_number, int value, uint64_t timeout) { return 0; }
	virtual void gpio_put(int pin_number, int value) {}
	virtual void set_led(bool value) {}
	virtual void sleep_us(int useconds) {}
public:
	int initialised_pin_number = 0;
	int pin_value = 0;
};

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
}



void GPIOTests::CleanUpAfterTests()
{
	hardwareInterface.release();
}