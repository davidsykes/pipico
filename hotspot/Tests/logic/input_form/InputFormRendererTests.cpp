#include <memory>
#include "TestFramework.h"
#include "InputFormRendererTests.h"
#include "input_form_renderer.h"

static std::unique_ptr<IInputFormRenderer> renderer;

static IInputFormRenderer* CreateTestObject()
{
	renderer.reset(new InputFormRenderer);
	return renderer.get();
}

void ASimpleFormCanBeRendered()
{
	IInputFormRenderer* renderer = CreateTestObject();

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
	renderer.release();
}