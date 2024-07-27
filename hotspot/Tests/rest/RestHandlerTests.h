#pragma once
#include "TestFramework.h"

class RestHandlerTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};