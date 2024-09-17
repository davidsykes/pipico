#pragma once
#include "TestFramework.h"

class GPIOTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};