#include <memory>
#include "TestFramework.h"
#include "WiFiConnectorTests.h"
#include "wifi_connector.h"


static std::unique_ptr<SYSTEM_INTERFACE_T> systemInterface;
static std::unique_ptr<WiFiConnector> wiFiConnector;
static uint8_t flashContents[256];

static const uint8_t* load_flash_data()
{
	return flashContents;
}

static WiFiConnector* CreateTestObject()
{
	systemInterface.reset(new SYSTEM_INTERFACE_T);
	systemInterface.get()->load_flash_data = &load_flash_data;
	WiFiConnector* wc = new WiFiConnector(systemInterface.get());
	wiFiConnector.reset(wc);

	return wiFiConnector.get();
}

static void MakeEmptyFlashContents()
{
	memcpy(flashContents, "random stuff", 12);
}

static void MakeSimpleCredentials()
{
	const char* bytes = "CREDuser name\0password\0";
	memcpy(flashContents, bytes, strlen(bytes));
}

static void IfNoCredentialsExistThenCredentialsAreValidIsFalse()
{
	MakeEmptyFlashContents();
	WiFiConnector* testObject = CreateTestObject();
	AssertFalse(testObject->CredentialsAreValid());
}

static void IfCredentialsExistThenCredentialsAreValidIsTrue()
{
	MakeSimpleCredentials();
	WiFiConnector* testObject = CreateTestObject();
	AssertTrue(testObject->CredentialsAreValid());
}


void WIFIConnectorTests::RunTests()
{
	IfNoCredentialsExistThenCredentialsAreValidIsFalse();
	IfCredentialsExistThenCredentialsAreValidIsTrue();
}


void WIFIConnectorTests::CleanUpAfterTests()
{
	systemInterface.release();
	wiFiConnector.release();
}