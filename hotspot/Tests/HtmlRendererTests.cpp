#include "Assert.h"
#include "HtmlRendererTests.h"
#include "..\logic\html_renderer.h"


void HtmlRendererTests::RunTests()
{
	RenderHtmlTest();
	RenderBodyTest();
	RenderHeaderTest();
	RenderParagraphTest();
}

void HtmlRendererTests::RenderHtmlTest()
{
	IHtmlRenderer* renderer = new HtmlRenderer();

	std::string html = renderer->RenderHtml("contents");

	AssertEqual(html, "<html>contents</html>");
}
void HtmlRendererTests::RenderBodyTest()
{
	IHtmlRenderer* renderer = new HtmlRenderer();

	std::string html = renderer->RenderBody("contents");

	AssertEqual(html, "<body>contents</body>");
}

void HtmlRendererTests::RenderHeaderTest()
{
	IHtmlRenderer* renderer = new HtmlRenderer();

	std::string html = renderer->RenderHeader("contents");

	AssertEqual(html, "<h1>contents</h1>");
}

void HtmlRendererTests::RenderParagraphTest()
{
	IHtmlRenderer* renderer = new HtmlRenderer();

	std::string html = renderer->RenderParagraph("contents");

	AssertEqual(html, "<p>contents</p>");
}
