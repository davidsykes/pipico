#pragma once
#include "TestFramework.h"


class HotSpotRequestRouterTests : public ITestModule
{
	virtual void CleanUpAfterTests();

public:
	void RunTests();
};