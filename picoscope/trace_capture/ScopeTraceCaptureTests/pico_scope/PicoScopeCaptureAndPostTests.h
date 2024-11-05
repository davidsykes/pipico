#pragma once
#include "TestFramework.h"

class PicoScopeCaptureAndPostTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};