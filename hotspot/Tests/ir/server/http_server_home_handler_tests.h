#pragma once
#include "TestFramework.h"

class HttpServerHomeHandlerTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};