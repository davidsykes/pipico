#pragma once
#include "TestFramework.h"

class IrControllerHttpRequestRouterTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};