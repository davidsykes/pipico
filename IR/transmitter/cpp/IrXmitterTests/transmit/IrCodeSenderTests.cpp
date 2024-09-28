#include <memory>
#include "IrCodeSenderTests.h"
#include "../Mocks/MockHardwareInteface.h"
#include "../../transmit/ir_code_sender.h"

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

static std::unique_ptr<IrCodeSender> objectUnderTest;
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

static IrCodeSender& CreateTestObject()
{
	CreateData();
	mockGPIOOutputPin.reset(new MockGPIOOutputPin);
	objectUnderTest.reset(new IrCodeSender(*mockGPIOOutputPin.get()));
	return *objectUnderTest.get();
}

static void AssertDataPoint(int i, int time, int value)
{
	AssertEqual(time, mockGPIOOutputPin.get()->Times[i]);
	AssertEqual(value, mockGPIOOutputPin.get()->Values[i]);
}

static void ACodeIsTransmitted()
{
	IIrCodeSender& sender = CreateTestObject();

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

void IrCodeSenderTests::RunTests()
{
	ACodeIsTransmitted();
}

void IrCodeSenderTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	irCode.release();
	mockGPIOOutputPin.release();
}
