#include "Assert.h"
#include "HotSpotConfigurationTests.h"
#include "..\configurations\hotspot_configuration.h"
#include "Mocks/MockHtmlRenderer.h"
#include "Mocks/MockInputFormRenderer.h"

void HotSpotConfigurationTests::SetUpObjectUnderTest()
{
	IHtmlRenderer* renderer = new MockHtmlRenderer();
	IInputFormRenderer* formRenderer = new MockInputFormRenderer();
	mockCredentialsHandler = new MockCredentialsHandler();
	config = new HotSpotConfiguration("description", renderer, formRenderer, mockCredentialsHandler);
}

void HotSpotConfigurationTests::RunTests()
{
	SetUpObjectUnderTest();
	GeneralRequestsReturnAnInputForm();
	SetUpObjectUnderTest();
	CredentialsSubmissionCallsCredentialsHandler();
}

void HotSpotConfigurationTests::GeneralRequestsReturnAnInputForm()
{
	std::string result = config->process_request("request", "params");

	AssertEqual(result, "html(body(h1(description)p(Enter Wifi Details){Form}))");
	AssertEqual(mockCredentialsHandler->HandledCredentials, "");
}

void HotSpotConfigurationTests::CredentialsSubmissionCallsCredentialsHandler()
{
	std::string result = config->process_request("/hotspotsubmit", "ssid=SSID&password=pass");

	AssertEqual(result, "");
	AssertEqual(mockCredentialsHandler->HandledCredentials, "ssid=SSID&password=pass");
}