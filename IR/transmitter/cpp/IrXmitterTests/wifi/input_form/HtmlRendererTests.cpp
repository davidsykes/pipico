#include <memory>
#include "TestFramework.h"
#include "HtmlRendererTests.h"
#include "../../wifi/input_form/html_renderer.h"

static std::unique_ptr<IHtmlRenderer> objectUnderTest;

static IHtmlRenderer* CreateTestObject()
{
	objectUnderTest.reset(new HtmlRenderer);
	return objectUnderTest.get();
}

void RenderHtmlTest()
{
	IHtmlRenderer* renderer = CreateTestObject();

	std::string html = renderer->RenderHtml("contents");

	AssertEqual("<html>contents</html>", html);
}

void RenderBodyTest()
{
	IHtmlRenderer* renderer = CreateTestObject();

	std::string html = renderer->RenderBody("contents");

	AssertEqual("<body>contents</body>", html);
}

void RenderHeaderTest()
{
	IHtmlRenderer* renderer = CreateTestObject();

	std::string html = renderer->RenderHeader("contents");

	AssertEqual("<h1>contents</h1>", html);
}

void RenderParagraphTest()
{
	IHtmlRenderer* renderer = CreateTestObject();

	std::string html = renderer->RenderParagraph("contents");

	AssertEqual("<p>contents</p>", html);
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
	objectUnderTest.release();
}