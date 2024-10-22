#include <memory>
#include "TestFramework.h"
#include "FlashParameterReaderTests.h"
#include "../../wifi/flash/flash_parameter_reader.h"


namespace
{
	class MockFlashHardware : public IFlashHardware
	{
		virtual const uint8_t* ReadFlash() { return (uint8_t*)FlashData; }
		virtual bool WriteFlash(const uint8_t* data) { Assert("Invalid"); }
	public:
		const char* FlashData = "xyzzySSID\0ssid\0Password\0password\0\0";
	};
}

static std::unique_ptr<FlashParameterReader> objectUnderTest;
static std::unique_ptr<MockFlashHardware> mockFlashHardware;

static FlashParameterReader* CreateTestObject()
{
	mockFlashHardware.reset(new MockFlashHardware);
	objectUnderTest.reset(new FlashParameterReader(*mockFlashHardware.get()));
	return objectUnderTest.get();
}

static void FlashParametersCanBeRead()
{
	IFlashParameterReader& reader = *CreateTestObject();

	reader.ReadParameters();

	AssertTrue(reader.ContainsParameter("SSID"));
	AssertEqual("ssid", reader.GetParameter("SSID"));
	AssertTrue(reader.ContainsParameter("Password"));
	AssertEqual("password", reader.GetParameter("Password"));
}

static void IfTheDataPrefixIsNotFoundThenNoParametersAreRead()
{
	IFlashParameterReader& reader = *CreateTestObject();

	reader.ReadParameters();

	AssertFalse(reader.ContainsParameter("SSID"));
	AssertFalse(reader.ContainsParameter("Password"));
}

static void IfTheDataExceedsTheBlockSizeThenNoFurtherParametersAreRead()
{
	IFlashParameterReader& reader = *CreateTestObject();

	reader.ReadParameters();

	AssertFalse(true);
}

void FlashParameterReaderTests::RunTests()
{
	FlashParametersCanBeRead();
	IfTheDataPrefixIsNotFoundThenNoParametersAreRead();
	IfTheDataExceedsTheBlockSizeThenNoFurtherParametersAreRead();
}

void FlashParameterReaderTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockFlashHardware.release();
}