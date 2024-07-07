#pragma once
#include "TestFramework.h"

class RestTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};