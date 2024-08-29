#pragma once
#include "TestFramework.h"

class HttpRequestRouterTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};