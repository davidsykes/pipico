#include <memory>
#include "TestFramework.h"
#include "FlashWriterTests.h"
#include "../../wifi/flash/flash_writer.h"


class MockFlashHardware : public IFlashHardware
{
	virtual const uint8_t* ReadFlash() { Assert("Invalid"); }
	virtual void WriteFlash(const uint8_t* data) { DataWritten = "dataah"; }
public:
	std::string DataWritten;
};

static std::unique_ptr<FlashWriter> objectUnderTest;
static std::unique_ptr<MockFlashHardware> mockFlashHardware;

static FlashWriter* CreateTestObject()
{
	mockFlashHardware.reset(new MockFlashHardware);
	objectUnderTest.reset(new FlashWriter(*mockFlashHardware.get()));
	return objectUnderTest.get();
}

static void ParameterDataIsWrittenToFlashSequentially()
{
	FlashWriter* writer = CreateTestObject();

	std::vector<FlashParameter> parameters;
	parameters.push_back(FlashParameter("Name 1", "Value 1"));
	parameters.push_back(FlashParameter("Name 2", "Value 2"));

	writer->WriteParameters(parameters);

	AssertEqual("Name 1\0Value 1\0Name 2\0Value 2\0\0", mockFlashHardware.get()->DataWritten);
}


void FlashWriterTests::RunTests()
{
	ParameterDataIsWrittenToFlashSequentially();
}

void FlashWriterTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockFlashHardware.release();
}