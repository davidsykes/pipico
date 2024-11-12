#include <memory>
#include "TestFramework.h"
#include "InputFormRendererTests.h"
#include "../../src/input_form/input_form_renderer.h"

static std::unique_ptr<IRenderer> objectUnderTest;

static IRenderer* CreateTestObject()
{
	objectUnderTest.reset(new InputFormRenderer);
	return objectUnderTest.get();
}

void ASimpleFormCanBeRendered()
{
	IRenderer* renderer = CreateTestObject();

	std::string html = renderer->Render();

	const char* expected = "<form action=\"/hotspotsubmit\" >"
		"<label for=\"ssid\">SSID:</label><br>"
		"<input type=\"text\" id=\"ssid\" name=\"ssid\" autofocus autocomplete=\"on\"><br>"
		"<label for=\"pass\">Password</label><br>"
		"<input type=\"password\" id=\"pass\" name=\"password\" autocomplete=\"on\" required/><br><br>"
		"<input type=\"submit\" value=\"Submit\">"
		"</form>";


	AssertEqualNonWhitespace(html.c_str(), expected);
}

void InputFormRendererTests::RunTests()
{
	ASimpleFormCanBeRendered();
}

void InputFormRendererTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}