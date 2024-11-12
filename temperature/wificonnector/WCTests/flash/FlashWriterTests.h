#pragma once
#include "TestFramework.h"


class FlashWriterTests : public ITestModule
{
	virtual void CleanUpAfterTests();

public:
	void RunTests();
};