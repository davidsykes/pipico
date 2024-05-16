#include <string>
#include "html_renderer.h"

std::string HtmlRenderer::RenderHtml(std::string contents)
{
	return "html(" + contents + ")";
}

std::string HtmlRenderer::RenderBody(std::string contents)
{
	return "body(" + contents + ")";
}

std::string HtmlRenderer::RenderHeader(std::string contents)
{
	return "h1(" + contents + ")";
}