#pragma once
#include "TestFramework.h"

class TcpRequestMakerTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};