#pragma once
#include "TestFramework.h"

class IrCodeRepositoryTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};