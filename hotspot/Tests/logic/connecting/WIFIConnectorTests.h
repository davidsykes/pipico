#pragma once
#include "TestFramework.h"


class WIFIConnectorTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	virtual void RunTests();
};