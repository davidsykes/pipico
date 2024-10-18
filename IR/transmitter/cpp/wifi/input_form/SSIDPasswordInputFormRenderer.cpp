#include "SSIDPasswordInputFormRenderer.h"

std::string SSIDPasswordInputFormRenderer::Render()
{
	return html_renderer.RenderHtml(
		html_renderer.RenderBody(
			html_renderer.RenderHeader(description) +
			html_renderer.RenderParagraph("Enter WiFi Details") +
			input_form.Render()
		));
}