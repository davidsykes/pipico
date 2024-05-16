#pragma once

#include "../logic/IHtmlRenderer.h"


class MockHtmlRenderer : public IHtmlRenderer
{
	virtual std::string RenderHtml(std::string contents);
	virtual std::string RenderBody(std::string contents);
	virtual std::string RenderHeader(std::string contents);
};