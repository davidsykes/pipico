#pragma once
#include "TestFramework.h"


class BlinkerTests : public ITestModule
{
	virtual void CleanUpAfterTests();

public:
	void RunTests();
};