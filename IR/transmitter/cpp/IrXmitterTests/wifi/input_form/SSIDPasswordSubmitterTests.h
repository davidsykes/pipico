#pragma once
#include "TestFramework.h"


class SSIDPasswordSubmitterTests : public ITestModule
{
	virtual void CleanUpAfterTests();

public:
	void RunTests();
};