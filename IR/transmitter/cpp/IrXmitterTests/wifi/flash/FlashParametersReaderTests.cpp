#include <memory>
#include "TestFramework.h"
#include "FlashParametersReaderTests.h"
#include "../../wifi/flash/flash_parameters_reader.h"
#include "../../wifi/flash/flash_constants.h"

namespace
{
	class MockFlashDataBlock
	{
		std::unique_ptr<uint8_t> FlashData;
	public:
		MockFlashDataBlock(int size);
		void SetFlashData(const char* data);
		void SetValidFlashData();
		uint8_t* GetFlashData() { return FlashData.get(); }
		void CreateTestDataBiggerThanABlock(int start);
	};
	class MockFlashHardware : public IFlashHardware
	{
		virtual const uint8_t* ReadFlash() { return dataBlock.GetFlashData(); }
		virtual bool WriteFlash(const uint8_t* data) { Assert("Invalid"); }

		MockFlashDataBlock& dataBlock;

	public:
		MockFlashHardware(MockFlashDataBlock& dataBlock) :dataBlock(dataBlock) {}
	};
}

static std::unique_ptr<FlashParametersReader> objectUnderTest;
static std::unique_ptr<MockFlashHardware> mockFlashHardware;
static std::unique_ptr<MockFlashDataBlock> mockFlashDataBlock;

static FlashParametersReader* CreateTestObject()
{
	mockFlashDataBlock.reset(new MockFlashDataBlock(FLASH_BLOCK_SIZE));
	mockFlashHardware.reset(new MockFlashHardware(*mockFlashDataBlock.get()));
	objectUnderTest.reset(new FlashParametersReader(*mockFlashHardware.get()));
	return objectUnderTest.get();
}

static void FlashParametersCanBeRead()
{
	IFlashParametersReader& reader = *CreateTestObject();
	mockFlashDataBlock.get()->SetValidFlashData();

	reader.ReadParameters();

	AssertTrue(reader.ContainsParameter("SSID"));
	AssertEqual("ssid", reader.GetParameter("SSID"));
	AssertTrue(reader.ContainsParameter("Password"));
	AssertEqual("password", reader.GetParameter("Password"));
}

static void WhenFlashParametersAreFoundReadParametersReturnsTrue()
{
	IFlashParametersReader& reader = *CreateTestObject();
	mockFlashDataBlock.get()->SetValidFlashData();

	bool result = reader.ReadParameters();

	AssertTrue(result);
}

static void IfTheDataPrefixIsNotFoundThenNoParametersAreRead()
{
	IFlashParametersReader& reader = *CreateTestObject();
	mockFlashDataBlock.get()->SetFlashData("Random stuff");

	reader.ReadParameters();

	AssertFalse(reader.ContainsParameter("SSID"));
	AssertFalse(reader.ContainsParameter("Password"));
}

static void IfTheDataPrefixIsNotFoundThenReadParametersReturnsFalse()
{
	IFlashParametersReader& reader = *CreateTestObject();
	mockFlashDataBlock.get()->SetFlashData("Random stuff");

	bool result = reader.ReadParameters();

	AssertFalse(result);
}

static void IfANameExceedsTheBlockSizeThenNoFurtherParametersAreRead()
{
	IFlashParametersReader& reader = *CreateTestObject();
	mockFlashDataBlock.get()->CreateTestDataBiggerThanABlock(20);

	bool result = reader.ReadParameters();

	AssertTrue(reader.ContainsParameter("SSID"));
	AssertFalse(reader.ContainsParameter("Password"));
	AssertFalse(result);
}

static void IfAValueExceedsTheBlockSizeThenNoFurtherParametersAreRead()
{
	IFlashParametersReader& reader = *CreateTestObject();
	mockFlashDataBlock.get()->CreateTestDataBiggerThanABlock(30);

	bool result = reader.ReadParameters();

	AssertTrue(reader.ContainsParameter("SSID"));
	AssertFalse(reader.ContainsParameter("Password"));
	AssertFalse(result);
}

static void UndefinedParametersReturnEmptyString()
{
	IFlashParametersReader& reader = *CreateTestObject();

	reader.ReadParameters();

	AssertEqual("", reader.GetParameter("undefined"));
}

//	MockFlashDataBlock

MockFlashDataBlock::MockFlashDataBlock(int size)
{
	FlashData.reset(new uint8_t[size]);
}

void MockFlashDataBlock::SetFlashData(const char* data)
{
	memcpy(FlashData.get(), data, strlen(data) + 1);
}

void MockFlashDataBlock::SetValidFlashData()
{
	memcpy(FlashData.get(), "xyzzySSID\0ssid\0Password\0password\0\0", 34);
};

void MockFlashDataBlock::CreateTestDataBiggerThanABlock(int start)
{
	SetValidFlashData();
	char* data = (char*)FlashData.get();
	for (int i = start; i < FLASH_BLOCK_SIZE; ++i)
		data[i] = 'x';
}

//	Test Class

void FlashParametersReaderTests::RunTests()
{
	FlashParametersCanBeRead();
	WhenFlashParametersAreFoundReadParametersReturnsTrue();
	IfTheDataPrefixIsNotFoundThenNoParametersAreRead();
	IfTheDataPrefixIsNotFoundThenReadParametersReturnsFalse();
	IfANameExceedsTheBlockSizeThenNoFurtherParametersAreRead();
	IfAValueExceedsTheBlockSizeThenNoFurtherParametersAreRead();
	UndefinedParametersReturnEmptyString();
}

void FlashParametersReaderTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockFlashHardware.release();
	mockFlashDataBlock.release();
}