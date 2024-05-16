#include <string>
#include "MockHtmlRenderer.h"

std::string MockHtmlRenderer::RenderHtml(std::string contents)
{
	return "html(" + contents + ")";
}

std::string MockHtmlRenderer::RenderBody(std::string contents)
{
	return "body(" + contents + ")";
}

std::string MockHtmlRenderer::RenderHeader(std::string contents)
{
	return "h1(" + contents + ")";
}

std::string MockHtmlRenderer::RenderParagraph(std::string contents)
{
	return "p(" + contents + ")";
}