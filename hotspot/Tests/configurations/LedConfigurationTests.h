#pragma once
#include "TestFramework.h"


class LedConfigurationTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};