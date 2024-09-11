#pragma once
#include "TestFramework.h"

class CodeDisplayFormatterTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};