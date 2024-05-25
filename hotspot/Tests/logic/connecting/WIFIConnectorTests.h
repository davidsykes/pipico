#pragma once
#include "TestFramework.h"


class WIFIConnectorTests : public ITestModule
{
	virtual void TearDownObjectUnderTest();
public:
	virtual void RunTests();
};