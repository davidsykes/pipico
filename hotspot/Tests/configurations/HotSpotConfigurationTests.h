#pragma once
#include "TestFramework.h"
#include "Mocks/MockCredentialsHandler.h"


class HotSpotConfigurationTests : public ITestModule
{
	virtual void CleanUpAfterTests();

public:
	void RunTests();
};