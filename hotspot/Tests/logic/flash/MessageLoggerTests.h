#pragma once
#include "TestFramework.h"


class MessageLoggerTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};