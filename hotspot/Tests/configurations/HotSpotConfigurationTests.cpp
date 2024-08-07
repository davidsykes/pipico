#include <memory>
#include "TestFramework.h"
#include "HotSpotConfigurationTests.h"
#include "hotspot_configuration.h"

class MockCredentialsHandler : public ICredentialsHandler
{
	virtual void HandleCredentials(std::string credentials);
public:
	std::string HandledCredentials;
};
class MockInputFormRenderer : public IInputFormRenderer
{
	virtual std::string Render();
};
class MockHtmlRenderer : public IHtmlRenderer
{
	virtual std::string RenderHtml(std::string contents);
	virtual std::string RenderBody(std::string contents);
	virtual std::string RenderHeader(std::string contents);
	virtual std::string RenderParagraph(std::string contents);
};

static std::unique_ptr<IHtmlRenderer> htmlRenderer;
static std::unique_ptr<IInputFormRenderer> formRenderer;
static std::unique_ptr<MockCredentialsHandler> mockCredentialsHandler;
static std::unique_ptr<HotSpotConfiguration> hotSpotConfiguration;

static TcpServer* CreateTestObject()
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

void MockCredentialsHandler::HandleCredentials(std::string credentials)
{
	HandledCredentials = credentials;
}

std::string MockInputFormRenderer::Render()
{
	return "{Form}";
}

std::string MockHtmlRenderer::RenderHtml(std::string contents)
{
	return "html(" + contents + ")";
}

std::string MockHtmlRenderer::RenderBody(std::string contents)
{
	return "body(" + contents + ")";
}

std::string MockHtmlRenderer::RenderHeader(std::string contents)
{
	return "h1(" + contents + ")";
}

std::string MockHtmlRenderer::RenderParagraph(std::string contents)
{
	return "p(" + contents + ")";
}