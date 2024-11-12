#pragma once
#include "TestFramework.h"


class HtmlRendererTests : public ITestModule
{
	virtual void CleanUpAfterTests();

public:
	void RunTests();
};