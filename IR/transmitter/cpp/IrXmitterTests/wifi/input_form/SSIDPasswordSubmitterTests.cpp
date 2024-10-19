#include <memory>
#include "TestFramework.h"
#include "SSIDPasswordSubmitterTests.h"
#include "../../Mocks\MockRenderer.h"
#include "../../../wifi/input_form/ssid_password_submitter.h"
//
//class MockHtmlRenderer : public IHtmlRenderer
//{
//	virtual std::string RenderHtml(std::string contents) { return "html(" + contents + ")"; }
//	virtual std::string RenderBody(std::string contents) { return "body(" + contents + ")"; }
//	virtual std::string RenderHeader(std::string contents) { return "head(" + contents + ")"; }
//	virtual std::string RenderParagraph(std::string contents) { return "p(" + contents + ")"; }
//};
//
//static std::unique_ptr<IHtmlRenderer> htmlRenderer;
//static std::unique_ptr<MockRenderer> formRenderer;
static std::unique_ptr<SSIDPasswordSubmitter> objectUnderTest;

static SSIDPasswordSubmitter& CreateTestObject()
{
	//htmlRenderer.reset(new MockHtmlRenderer);
	//formRenderer.reset(new MockRenderer("Form"));
	objectUnderTest.reset(new SSIDPasswordSubmitter());

	return *objectUnderTest.get();
}

static void TheSubmittedParametersArePassedToTheFlashWriter()
{
	IRenderer& submitter = CreateTestObject();

	std::string result = submitter.Render();

	AssertEqual("html(body(head(description)p(Enter WiFi Details)Form))", result);
}

static void TheSubmitterReturnsOk()
{
	IRenderer& submitter = CreateTestObject();

	std::string result = submitter.Render();

	AssertEqual("html(body(head(description)p(Enter WiFi Details)Form))", result);
}

void SSIDPasswordSubmitterTests::RunTests()
{
	TheSubmittedParametersArePassedToTheFlashWriter();
	TheSubmitterReturnsOk();
}

void SSIDPasswordSubmitterTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}
