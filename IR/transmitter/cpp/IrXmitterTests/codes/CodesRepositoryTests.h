#pragma once
#include "TestFramework.h"

class CodesRepositoryTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};