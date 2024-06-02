#include <memory>
#include "FlashManagerTests.h"
#include "flash_manager.h"


static std::unique_ptr<IFlashHardware> flashHardware;
static uint8_t flashContents[FLASH_PAGE_SIZE];
static std::unique_ptr<FlashManager> flashManager;

std::string MakeStringWithLength(int len);

class MockFMFlashHardware : public IFlashHardware
{
	virtual const uint8_t* ReadFlash() { return 0; }
	virtual void WriteFlash(const uint8_t*data) { memcpy(flashContents, data, FLASH_PAGE_SIZE); }
};

static IFlashManager* CreateTestObject()
{
	flashHardware.reset(new MockFMFlashHardware());
	flashManager.reset(new FlashManager(flashHardware.get()));
	return flashManager.get();
}

static void BasicValuesCanBeWrittenToTheFlash()
{
	CreateTestObject()->WriteToFlash("ssid", "password", "error");

	const char* expected = FLASH_CREDENTIALS_PREFIX "ssid\0password\0error\0";
	AssertEqual(0, memcmp(flashContents, expected, 24));
}

static void CredentialDataCanFillAFlashPage()
{
	int spaceForCredentials = FLASH_PAGE_SIZE - FLASH_CREDENTIALS_PREFIX_LEN;
	int equalStringLengthWithNullTerminator = (spaceForCredentials / 3);
	int equalStringLengthWithoutNullTerminator = equalStringLengthWithNullTerminator - 1;
	auto s = MakeStringWithLength(equalStringLengthWithoutNullTerminator);

	CreateTestObject()->WriteToFlash(s, s, s);

	const char* fc = (const char*)flashContents;
	AssertEqual(fc, (std::string(FLASH_CREDENTIALS_PREFIX) + s).c_str());
	AssertEqual(fc + FLASH_CREDENTIALS_PREFIX_LEN + equalStringLengthWithNullTerminator, s.c_str());
	AssertEqual(fc + FLASH_CREDENTIALS_PREFIX_LEN + equalStringLengthWithNullTerminator * 2, s.c_str());
}

static void IfValuesExceedSizeOfFlashPageAnErrorIsWritten()
{
	int spaceForCredentials = FLASH_PAGE_SIZE - FLASH_CREDENTIALS_PREFIX_LEN;
	int equalStringLengthWithNullTerminator = (spaceForCredentials / 3);
	int equalStringLengthWithoutNullTerminator = equalStringLengthWithNullTerminator - 1;
	auto s = MakeStringWithLength(equalStringLengthWithoutNullTerminator);

	CreateTestObject()->WriteToFlash(s, s, s + "!");

	AssertEqual(0, memcmp(flashContents, FLASH_CREDENTIALS_PREFIX "\0\0Data size error.\0", FLASH_CREDENTIALS_PREFIX_LEN + 19));
}

void FlashManagerTests::RunTests()
{
	BasicValuesCanBeWrittenToTheFlash();
	CredentialDataCanFillAFlashPage();
	IfValuesExceedSizeOfFlashPageAnErrorIsWritten();
}

void FlashManagerTests::CleanUpAfterTests()
{
	flashHardware.release();
	flashManager.release();
}

std::string MakeStringWithLength(int len)
{
	std::string s = "1234567890";
	while (s.length() < len)
	{
		s = s + s;
	}
	return s.substr(0, len);
}