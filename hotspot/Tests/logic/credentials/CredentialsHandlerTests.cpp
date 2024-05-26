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
	virtual void WriteToFlash(const std::string& SSID, const std::string& password);
public:
	std::string SSID;
	std::string password;
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
}

static void MissingSSIDGeneratesAnError()
{
	AssertTrue(false);
}

static void MissingPasswordGeneratesAnError()
{
	AssertTrue(false);
}

static void CredentialDataCanFillAFlashPage()
{
	AssertTrue(false);
}

static void CredentialDataCannotExceedAFlashPage()
{
	AssertTrue(false);
}

void CredentialsHandlerTests::RunTests()
{
	ConvertedCredentialsAreStoredInTheFlash();
	MissingSSIDGeneratesAnError();
	MissingPasswordGeneratesAnError();
	CredentialDataCanFillAFlashPage();
	CredentialDataCannotExceedAFlashPage();
}


void CredentialsHandlerTests::TearDownObjectUnderTest()
{
	handler.release();
}


void MockFlashManager::WriteToFlash(const std::string& SSID, const std::string& password)
{
	this->SSID = SSID;
	this->password = password;
}


std::string MockPercentDecoder::Decode(const std::string& value)
{
	return "converted " + value;
}

