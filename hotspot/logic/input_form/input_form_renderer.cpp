#include <string>
#include "input_form_renderer.h"


std::string InputFormRenderer::Render()
{
	const char* form_header = "<form action=\"/hotspotsubmit\">";

	const char* ssid_label = "<label for=\"ssid\">SSID:</label><br>"
		"<input type=\"text\" id=\"ssid\" name=\"ssid\" autofocus autocomplete=\"on\"><br>";

	const char* password_label = "<label for=\"pass\">Password</label><br>"
		"<input type=\"password\" id=\"pass\" name=\"password\" autocomplete=\"on\" required/><br><br>";

	const char* submit = "<input type=\"submit\" value=\"Submit\">";

	const char* form_end = "</form>";

	return std::string(form_header) + ssid_label + password_label + submit + form_end;
}