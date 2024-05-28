#pragma once
#include "TestFramework.h"


class FlashManagerTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};