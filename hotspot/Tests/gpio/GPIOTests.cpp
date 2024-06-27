#include "GPIOTests.h"
#include "../../work/gpio/gpio.h"


void GPIOTests::RunTests()
{
	GPIOInputPin ip(5, hw_if);

	bool result = ip.Value();

	AssertTrue(result);
}
