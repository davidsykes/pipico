#include "SSIDPasswordInputFormRenderer.h"

std::string SSIDPasswordInputFormRenderer::RouteHttpRequest(const char* request)
{
	return html_renderer.RenderHtml(
		html_renderer.RenderBody(
			html_renderer.RenderHeader(description) +
			html_renderer.RenderParagraph("Enter WiFi Details") +
			input_form.Render()
		));
}