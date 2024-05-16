#pragma once


class IHtmlRenderer
{
public:
	virtual std::string RenderHtml(std::string contents) = 0;
	virtual std::string RenderBody(std::string contents) = 0;
	virtual std::string RenderHeader(std::string contents) = 0;
};