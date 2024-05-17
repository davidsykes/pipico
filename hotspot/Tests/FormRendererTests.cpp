#include "Assert.h"
#include "FormRendererTests.h"
#include "..\logic\input_form_renderer.h"


void FormRendererTests::RunTests()
{
	ASimpleFormCanBeRendered();
}

void FormRendererTests::ASimpleFormCanBeRendered()
{
	IInputFormRenderer* renderer = new InputFormRenderer();

	std::string html = renderer->Render();

	const char* expected = "<form action=\"/hotspotsubmit\" >"
		"<label for=\"ssid\">SSID:</label><br>"
		"<input type=\"text\" id=\"ssid\" name=\"ssid\"><br>"
		"<label for=\"pass\">Password</label><br>"
		"<input type=\"password\" id=\"pass\" name=\"password\" autocomplete=\"on\" required/><br><br>"
		"<input type=\"submit\" value=\"Submit\">"
		"</form>";


	AssertEqualNonWhitespace(html.c_str(), expected);
}
