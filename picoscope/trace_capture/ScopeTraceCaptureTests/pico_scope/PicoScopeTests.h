#pragma once
#include "TestFramework.h"

class PicoScopeTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};