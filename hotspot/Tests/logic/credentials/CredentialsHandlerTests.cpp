#include <memory>
#include "TestFramework.h"
#include "CredentialsHandlerTests.h"
#include "credentials_handler.h"

class MockPercentDecoder : public IPercentDecoder
{
	virtual std::string Decode(const std::string& value);
};

class MockFlashManager : public IFlashManager
{
	virtual void WriteToFlash(const std::string& SSID, const std::string& password, const std::string& error);
public:
	std::string SSID;
	std::string password;
	std::string error;
};

static std::unique_ptr<MockPercentDecoder> mockPercentDecoder;
static std::unique_ptr<MockFlashManager> mockFlashManager;
static std::unique_ptr<CredentialsHandler> handler;

static CredentialsHandler* CreateTestObject()
{
	mockPercentDecoder.reset(new MockPercentDecoder());
	mockFlashManager.reset(new MockFlashManager());
	handler.reset(new CredentialsHandler(mockPercentDecoder.get(), mockFlashManager.get()));
	return handler.get();
}

static void ConvertedCredentialsAreStoredInTheFlash()
{
	std::string credentialsString = "ssid=ssid name&password=123456";
	CredentialsHandler* handler = CreateTestObject();

	handler->HandleCredentials(credentialsString);

	AssertEqual(mockFlashManager.get()->SSID, "converted ssid name");
	AssertEqual(mockFlashManager.get()->password, "converted 123456");
	AssertEqual(mockFlashManager.get()->error, "");
}

static void MissingSSIDGeneratesAnError()
{
	std::string credentialsString = "NOssid=ssid name&password=123456";
	CredentialsHandler* handler = CreateTestObject();

	handler->HandleCredentials(credentialsString);

	AssertEqual(mockFlashManager.get()->SSID, "");
	AssertEqual(mockFlashManager.get()->password, "");
	AssertEqual(mockFlashManager.get()->error, "SSID not found.");
}

static void MissingAmpersandGeneratesAnError()
{
	std::string credentialsString = "ssid=ssid name password=123456";
	CredentialsHandler* handler = CreateTestObject();

	handler->HandleCredentials(credentialsString);

	AssertEqual(mockFlashManager.get()->SSID, "");
	AssertEqual(mockFlashManager.get()->password, "");
	AssertEqual(mockFlashManager.get()->error, "Password not found.");
}

static void MissingPasswordGeneratesAnError()
{
	std::string credentialsString = "ssid=ssid name&NOpassword=123456";
	CredentialsHandler* handler = CreateTestObject();

	handler->HandleCredentials(credentialsString);

	AssertEqual(mockFlashManager.get()->SSID, "");
	AssertEqual(mockFlashManager.get()->password, "");
	AssertEqual(mockFlashManager.get()->error, "Password not found.");
}

void CredentialsHandlerTests::RunTests()
{
	ConvertedCredentialsAreStoredInTheFlash();
	MissingSSIDGeneratesAnError();
	MissingAmpersandGeneratesAnError();
	MissingPasswordGeneratesAnError();
}


void CredentialsHandlerTests::CleanUpAfterTests()
{
	mockPercentDecoder.release();
	mockFlashManager.release();
	handler.release();
}


void MockFlashManager::WriteToFlash(const std::string& SSID, const std::string& password, const std::string& error)
{
	this->SSID = SSID;
	this->password = password;
	this->error = error;
}


std::string MockPercentDecoder::Decode(const std::string& value)
{
	return "converted " + value;
}

