#pragma once
#include "TestFramework.h"

class HttpServerRecordHandlerTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};