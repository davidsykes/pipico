#include <memory>
#include "TestFramework.h"
#include "SSIDPasswordInputFormRendererTests.h"
#include "../../Mocks\MockRenderer.h"
#include "../../../wifi/input_form/ssid_password_input_form_renderer.h"

class MockHtmlRenderer : public IHtmlRenderer
{
	virtual std::string RenderHtml(std::string contents) { return "html(" + contents + ")"; }
	virtual std::string RenderBody(std::string contents) { return "body(" + contents + ")"; }
	virtual std::string RenderHeader(std::string contents) { return "head(" + contents + ")"; }
	virtual std::string RenderParagraph(std::string contents) { return "p(" + contents + ")"; }
};

static std::unique_ptr<IHtmlRenderer> htmlRenderer;
static std::unique_ptr<MockRenderer> formRenderer;
static std::unique_ptr<SSIDPasswordInputFormRenderer> objectUnderTest;

static SSIDPasswordInputFormRenderer& CreateTestObject()
{
	htmlRenderer.reset(new MockHtmlRenderer);
	formRenderer.reset(new MockRenderer("Form"));
	objectUnderTest.reset(new SSIDPasswordInputFormRenderer(
		"description",
		*htmlRenderer.get(),
		*formRenderer.get()
	));

	return *objectUnderTest.get();
}

static void TheInputFormIsRendered()
{
	IRenderer& renderer = CreateTestObject();

	std::string result = renderer.Render();

	AssertEqual("html(body(head(description)p(Enter WiFi Details)Form))", result);
}

void SSIDPasswordInputFormRendererTests::RunTests()
{
	TheInputFormIsRendered();
}

void SSIDPasswordInputFormRendererTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	htmlRenderer.release();
	formRenderer.release();
}
