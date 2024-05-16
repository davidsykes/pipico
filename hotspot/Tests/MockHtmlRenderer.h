#pragma once

#include "../logic/ihtml_renderer.h"


class MockHtmlRenderer : public IHtmlRenderer
{
	virtual std::string RenderHtml(std::string contents);
	virtual std::string RenderBody(std::string contents);
	virtual std::string RenderHeader(std::string contents);
	virtual std::string RenderParagraph(std::string contents);
};