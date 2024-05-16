#include <string>
#include "html_renderer.h"

std::string HtmlRenderer::RenderHtml(std::string contents)
{
	return "<html>" + contents + "</html>";
}

std::string HtmlRenderer::RenderBody(std::string contents)
{
	return "<body>" + contents + "</body>";
}

std::string HtmlRenderer::RenderHeader(std::string contents)
{
	return "<h1>" + contents + "</h1>";
}