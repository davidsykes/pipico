#include <memory>
#include "TestFramework.h"
#include "HotSpotConfigurationTests.h"
#include "hotspot_configuration.h"
#include "Mocks/MockHtmlRenderer.h"
#include "Mocks/MockInputFormRenderer.h"


static std::unique_ptr<IHtmlRenderer> htmlRenderer;
static std::unique_ptr<IInputFormRenderer> formRenderer;
static std::unique_ptr<MockCredentialsHandler> mockCredentialsHandler;
static std::unique_ptr<HotSpotConfiguration> hotSpotConfiguration;

static Configuration* CreateTestObject()
{
	htmlRenderer.reset(new MockHtmlRenderer);
	formRenderer.reset(new MockInputFormRenderer);
	mockCredentialsHandler.reset(new MockCredentialsHandler);
	hotSpotConfiguration.reset(new HotSpotConfiguration(
		"description",
		"last error",
		htmlRenderer.get(),
		formRenderer.get(),
		mockCredentialsHandler.get()));
	return hotSpotConfiguration.get();
}

void GeneralRequestsReturnAnInputForm()
{
	auto config = CreateTestObject();

	std::string result = config->process_request("request", "params");

	AssertEqual(result, "html(body(h1(description)p(Enter WiFi Details){Form}))");
	AssertEqual(mockCredentialsHandler->HandledCredentials, "");
}

void CredentialsSubmissionCallsCredentialsHandler()
{
	auto config = CreateTestObject();

	std::string result = config->process_request("/hotspotsubmit", "ssid=SSID&password=pass");

	AssertEqual(result, "");
	AssertEqual(mockCredentialsHandler->HandledCredentials, "ssid=SSID&password=pass");
}


void HotSpotConfigurationTests::RunTests()
{
	GeneralRequestsReturnAnInputForm();
	CredentialsSubmissionCallsCredentialsHandler();
}

void HotSpotConfigurationTests::CleanUpAfterTests()
{
	htmlRenderer.release();
	formRenderer.release();
	mockCredentialsHandler.release();
	hotSpotConfiguration.release();
}