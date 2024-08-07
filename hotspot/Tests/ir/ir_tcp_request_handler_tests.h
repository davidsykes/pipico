#pragma once
#include "TestFramework.h"

class IrTcpRequestHandlerTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};