#include <memory>
#include "IrSignalSenderTests.h"
#include "../Mocks/MockHardwareInteface.h"
#include "../../transmit/ir_signal_sender.h"

namespace
{
	class MockGPIOOutputPin : public IGPIOOutputPin
	{
		virtual void SetValue(bool value);
		virtual uint64_t SetValueAt(bool value, uint64_t time_us);

	public:
		size_t size() const { return Times.size(); }
		std::vector<uint64_t> Times;
		std::vector<int> Values;
	};
}

static std::unique_ptr<IrSignalSender> irSignalSender;
static std::unique_ptr<MockGPIOOutputPin> mockGPIOOutputPin;
static std::unique_ptr<IrCode> irCode;

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
	mockGPIOOutputPin.reset(new MockGPIOOutputPin);
	irSignalSender.reset(new IrSignalSender(*mockGPIOOutputPin.get()));
	return *irSignalSender.get();
}

static void AssertDataPoint(int i, int time, int value)
{
	AssertEqual(time, mockGPIOOutputPin.get()->Times[i]);
	AssertEqual(value, mockGPIOOutputPin.get()->Values[i]);
}

static void ACodeIsTransmitted()
{
	IIrSignalSender& sender = CreateTestObject();

	sender.SendCode(*irCode.get());

	MockGPIOOutputPin& mi = *mockGPIOOutputPin.get();

	AssertEqual(3, mi.size());
	AssertDataPoint(0, 0, 1);
	AssertDataPoint(1, 102, 0);
	AssertDataPoint(2, 302, 1);
}


void MockGPIOOutputPin::SetValue(bool value)
{
	Assert("Invalid call");
}

uint64_t MockGPIOOutputPin::SetValueAt(bool value, uint64_t time_us)
{
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
	mockGPIOOutputPin.release();
	irSignalSender.release();
}
