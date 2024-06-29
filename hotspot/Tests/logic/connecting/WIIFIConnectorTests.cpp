#include <memory>
#include "TestFramework.h"
#include "WiFiConnectorTests.h"
#include "wifi_connection_maker.h"
#include "flash_hardware.h"


static std::unique_ptr<IFlashHardware> flashHardware;
static std::unique_ptr<WiFiConnectionMaker> wiFiConnector;
static uint8_t flashContents[256];

class MockWCFlashHardware : public IFlashHardware
{
	virtual const uint8_t* ReadFlash()
	{
		return flashContents;
	}
	virtual void WriteFlash(const uint8_t*) {}
};

static WiFiConnectionMaker* CreateTestObject()
{
	flashHardware.reset(new MockWCFlashHardware());
	WiFiConnectionMaker* wc = new WiFiConnectionMaker(flashHardware.get());
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
	WiFiConnectionMaker* testObject = CreateTestObject();
	AssertFalse(testObject->CredentialsAreValid());
}

static void IfCredentialsExistThenCredentialsAreValidIsTrue()
{
	MakeSimpleCredentials();
	WiFiConnectionMaker* testObject = CreateTestObject();
	AssertTrue(testObject->CredentialsAreValid());
}


void WIFIConnectorTests::RunTests()
{
	IfNoCredentialsExistThenCredentialsAreValidIsFalse();
	IfCredentialsExistThenCredentialsAreValidIsTrue();
}


void WIFIConnectorTests::CleanUpAfterTests()
{
	flashHardware.release();
	wiFiConnector.release();
}