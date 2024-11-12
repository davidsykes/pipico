#pragma once

class ITestModule
{
	virtual void CleanUpAfterTests() = 0;
public:
	virtual void RunTests() = 0;
};
