#pragma once
#include "TestFramework.h"

class HttpServerHomePageTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};