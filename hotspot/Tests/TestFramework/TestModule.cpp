#include "ITestModule.h"






#include "stdio.h"

void ITestModule2::RunTests()
{
	printf("boo hoo");
}

void ITestModule2::RunTest(void (*fn)(void* p))
{
	void* obj = SetUpObjectUnderTest();
	fn(obj);
	TearDownObjectUnderTest(obj);
}

void ITestModule2::TearDownObjectUnderTest(void *obj)
{
	delete(obj);
}
