#pragma once
#include "TestFramework.h"


class IrCodeSenderTests : public ITestModule
{
	virtual void CleanUpAfterTests();

public:
	void RunTests();
};