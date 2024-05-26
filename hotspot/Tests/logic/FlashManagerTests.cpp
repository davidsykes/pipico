#include <memory>
#include "FlashManagerTests.h"
#include "flash_manager.h"
#include "system_interface.h"

constexpr auto FLASH_PAGE_SIZE = 256;

static std::unique_ptr<SYSTEM_INTERFACE_T> systemInterface;
static uint8_t flashContents[256];
static std::unique_ptr<FlashManager> flashManager;

static void write_flash_data(const uint8_t* data)
{
	memcpy(flashContents, data, FLASH_PAGE_SIZE);
}

static IFlashManager* CreateTestObject()
{
	systemInterface.reset(new SYSTEM_INTERFACE_T);
	systemInterface.get()->write_flash_data = &write_flash_data;
	flashManager.reset(new FlashManager(systemInterface.get()));
	return flashManager.get();
}

void FlashManagerTests::RunTests()
{
	BasicValuesCanBeWrittenToTheFlash();
	IfValuesExceedSizeOfFlashPageAnErrorIsWritten();
}

void FlashManagerTests::BasicValuesCanBeWrittenToTheFlash()
{
	AssertTrue(false);
}

void FlashManagerTests::IfValuesExceedSizeOfFlashPageAnErrorIsWritten()
{
	AssertTrue(false);
}


//
//static void MakeEmptyFlashContents()
//{
//	memcpy(flashContents, "random stuff", 12);
//}
//
//static void MakeSimpleCredentials()
//{
//	const char* bytes = "CREDuser name\0password\0";
//	memcpy(flashContents, bytes, strlen(bytes));
//}
//
//static void IfNoCredentialsExistThenCredentialsAreValidIsFalse()
//{
//	MakeEmptyFlashContents();
//	WiFiConnector* testObject = CreateTestObject();
//	AssertFalse(testObject->CredentialsAreValid());
//}
//
//static void IfCredentialsExistThenCredentialsAreValidIsTrue()
//{
//	MakeSimpleCredentials();
//	WiFiConnector* testObject = CreateTestObject();
//	AssertTrue(testObject->CredentialsAreValid());
//}