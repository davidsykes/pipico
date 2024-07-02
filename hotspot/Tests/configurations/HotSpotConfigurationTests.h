#pragma once
#include "TestFramework.h"


class HotSpotConfigurationTests : public ITestModule
{
	virtual void CleanUpAfterTests();

public:
	void RunTests();
};