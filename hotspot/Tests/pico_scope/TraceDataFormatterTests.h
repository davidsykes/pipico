#pragma once
#include "TestFramework.h"

class TraceDataFormatterTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};