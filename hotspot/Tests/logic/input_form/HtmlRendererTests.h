#pragma once
#include "TestFramework.h"


class HtmlRendererTests : public ITestModule
{
	void RenderHtmlTest();
	void RenderBodyTest();
	void RenderHeaderTest();
	void RenderParagraphTest();

public:
	void RunTests();
};