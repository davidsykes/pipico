#include <memory>
#include "IrSignalSenderTests.h"
#include "../Mocks/MockHardwareInteface.h"
#include "../../transmit/ir_signal_sender.h"

namespace
{
	class MockHardwareInterface : public IMockHardwareInterface
	{
		virtual uint64_t gpio_put_at_us(int pin_number, bool value, int time_us);
	public:
		size_t size() const { return Times.size(); }
		std::vector<int> Pins;
		std::vector<int> Times;
		std::vector<int> Values;
	};
}

static std::unique_ptr<IrSignalSender> irSignalSender;
static std::unique_ptr<MockHardwareInterface> mockHardwareInterface;
static std::unique_ptr<IrCode> irCode;
const int pin_number = 42;

static void CreateDataPoint(int time, int value)
{
	IrCode& ir = *irCode.get();
	ir.Times.push_back(time);
	ir.Values.push_back(value);
}

static void CreateData()
{
	irCode.reset(new IrCode);
	irCode.get()->Count = 3;
	CreateDataPoint(0, 1);
	CreateDataPoint(100, 0);
	CreateDataPoint(300, 1);
}

static IrSignalSender& CreateTestObject()
{
	CreateData();
	mockHardwareInterface.reset(new MockHardwareInterface);
	irSignalSender.reset(new IrSignalSender(*mockHardwareInterface.get(), pin_number));
	return *irSignalSender.get();
}

static void AssertDataPoint(int i, int time, int value)
{
	AssertEqual(pin_number, mockHardwareInterface.get()->Pins[i]);
	AssertEqual(time, mockHardwareInterface.get()->Times[i]);
	AssertEqual(value, mockHardwareInterface.get()->Values[i]);
}

static void ACodeIsTransmitted()
{
	IIrSignalSender& sender = CreateTestObject();

	sender.SendCode(*irCode.get());

	MockHardwareInterface& mi = *mockHardwareInterface.get();

	AssertEqual(3, mi.size());
	AssertDataPoint(0, 0, 1);
	AssertDataPoint(1, 102, 0);
	AssertDataPoint(2, 302, 1);
}

uint64_t MockHardwareInterface::gpio_put_at_us(int pin_number, bool value, int time_us)
{
	Pins.push_back(pin_number);
	Times.push_back(time_us);
	Values.push_back(value);
	return time_us + 2;
}

void IrSignalSenderTests::RunTests()
{
	ACodeIsTransmitted();
}

void IrSignalSenderTests::CleanUpAfterTests()
{
	irCode.release();
	irSignalSender.release();
}
