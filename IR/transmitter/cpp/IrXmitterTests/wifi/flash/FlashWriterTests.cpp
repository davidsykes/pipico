#include <memory>
#include "TestFramework.h"
#include "FlashWriterTests.h"
#include "../../wifi/flash/flash_writer.h"
#include "../../wifi/flash/flash_constants.h"

namespace
{
	class MockFlashHardware : public IFlashHardware
	{
		virtual const uint8_t* ReadFlash() { Assert("Invalid"); }
		virtual bool WriteFlash(const uint8_t* data) { DataWritten = data; return ReturnValue; }
	public:
		const uint8_t* DataWritten = 0;
		bool ReturnValue = true;
	};
}

static std::unique_ptr<FlashWriter> objectUnderTest;
static std::unique_ptr<MockFlashHardware> mockFlashHardware;
static std::vector<FlashParameter> parameters;

static FlashWriter* CreateTestObject()
{
	parameters.clear();
	parameters.push_back(FlashParameter("Name 1", "Value 1"));
	parameters.push_back(FlashParameter("Name 2", "Value 2"));

	mockFlashHardware.reset(new MockFlashHardware);
	objectUnderTest.reset(new FlashWriter(*mockFlashHardware.get()));
	return objectUnderTest.get();
}

static void ParameterDataIsWrittenToFlashSequentially()
{
	IFlashWriter* writer = CreateTestObject();

	writer->WriteParameters(parameters);

	const uint8_t* dataWritten = mockFlashHardware.get()->DataWritten;

	AssertEqual(0, memcmp(FLASH_PARAMETERS_PREFIX "Name 1\0Value 1\0Name 2\0Value 2\0\0", dataWritten, 31));
}

static void WriteParametersReturnsTrueWhenParametersAreSuccessfullyWritten()
{
	IFlashWriter* writer = CreateTestObject();

	bool value = writer->WriteParameters(parameters);

	AssertTrue(value);
}

static void WriteParametersReturnsFalseWhenParametersAreNotSuccessfullyWritten()
{
	IFlashWriter* writer = CreateTestObject();
	mockFlashHardware.get()->ReturnValue = false;

	bool value = writer->WriteParameters(parameters);

	AssertFalse(value);
}

static void IfNoParametersAreProvidedNothingIsWritten()
{
	IFlashWriter* writer = CreateTestObject();
	parameters.clear();

	bool value = writer->WriteParameters(parameters);

	AssertTrue(value);
	AssertTrue(mockFlashHardware.get()->DataWritten == 0);
}

static void FillParametersWithEnoughDataToExceedTheBlockSize()
{
	parameters.clear();
	const char* testString10CharactersLong = "123456789";
	int sizeOfTestParameter = 20;
	int numberOfParametersThatWillFit = FLASH_BLOCK_SIZE / sizeOfTestParameter;
	int numberOfParametersToPutIn = numberOfParametersThatWillFit + 1;
	for (int x = 0; x < numberOfParametersToPutIn; ++x)
	{
		parameters.push_back(FlashParameter(testString10CharactersLong, testString10CharactersLong));
	}
}

static void IfParametersExceedTheFlashBlockSizeThenNothingIsWritten()
{
	IFlashWriter* writer = CreateTestObject();
	FillParametersWithEnoughDataToExceedTheBlockSize();

	bool value = writer->WriteParameters(parameters);

	AssertFalse(value);
	AssertTrue(mockFlashHardware.get()->DataWritten == 0);
}

void FlashWriterTests::RunTests()
{
	ParameterDataIsWrittenToFlashSequentially();
	WriteParametersReturnsTrueWhenParametersAreSuccessfullyWritten();
	WriteParametersReturnsFalseWhenParametersAreNotSuccessfullyWritten();
	IfNoParametersAreProvidedNothingIsWritten();
	IfParametersExceedTheFlashBlockSizeThenNothingIsWritten();
}

void FlashWriterTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockFlashHardware.release();
	parameters.clear();
}