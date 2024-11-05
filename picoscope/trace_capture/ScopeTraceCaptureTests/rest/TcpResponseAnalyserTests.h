#pragma once
#include "TestFramework.h"

class TcpResponseAnalyserTests : public ITestModule
{
	virtual void CleanUpAfterTests();
public:
	void RunTests();
};