#include <memory>
#include "TestFramework.h"
#include "HtmlRendererTests.h"
#include "../../wifi/input_form/html_renderer.h"

static std::unique_ptr<IHtmlRenderer> htmlRenderer;

static IHtmlRenderer* CreateTestObject()
{
	htmlRenderer.reset(new HtmlRenderer);
	return htmlRenderer.get();
}

void RenderHtmlTest()
{
	IHtmlRenderer* renderer = CreateTestObject();

	std::string html = renderer->RenderHtml("contents");

	AssertEqual(html, "<html>contents</html>");
}

void RenderBodyTest()
{
	IHtmlRenderer* renderer = CreateTestObject();

	std::string html = renderer->RenderBody("contents");

	AssertEqual(html, "<body>contents</body>");
}

void RenderHeaderTest()
{
	IHtmlRenderer* renderer = CreateTestObject();

	std::string html = renderer->RenderHeader("contents");

	AssertEqual(html, "<h1>contents</h1>");
}

void RenderParagraphTest()
{
	IHtmlRenderer* renderer = CreateTestObject();

	std::string html = renderer->RenderParagraph("contents");

	AssertEqual(html, "<p>contents</p>");
}

void HtmlRendererTests::RunTests()
{
	RenderHtmlTest();
	RenderBodyTest();
	RenderHeaderTest();
	RenderParagraphTest();
}

void HtmlRendererTests::CleanUpAfterTests()
{
	htmlRenderer.release();
}