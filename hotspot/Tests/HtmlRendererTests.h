#pragma once
#include "ITestModule.h"


class HtmlRendererTests : public ITestModule
{
	void RenderHtmlTest();
	void RenderBodyTest();
	void RenderHeaderTest();

public:
	void RunTests();
};