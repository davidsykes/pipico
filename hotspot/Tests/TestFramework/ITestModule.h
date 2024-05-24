#pragma once

class ITestModule
{
public:
	virtual void RunTests() = 0;
};

class ITestModule2
{
	virtual void* SetUpObjectUnderTest() = 0;
	virtual void TearDownObjectUnderTest(void *);

public:
	void RunTest(void (*fn)(void* p));

	virtual void RunTests();
};