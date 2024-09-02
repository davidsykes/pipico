#pragma once
#include "TestFramework.h"

class HttpResponsePackagerTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};