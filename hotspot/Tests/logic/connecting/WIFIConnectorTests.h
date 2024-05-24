#pragma once
#include "ITestModule.h"


class WIFIConnectorTests : public ITestModule2
{
	virtual void* SetUpObjectUnderTest();
public:
	WIFIConnectorTests();
};