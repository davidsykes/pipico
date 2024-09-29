#pragma once
#include "TestFramework.h"

class CodeSequenceRepositoryTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};