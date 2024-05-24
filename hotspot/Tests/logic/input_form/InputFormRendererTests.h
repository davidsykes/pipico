#pragma once
#include "ITestModule.h"


class InputFormRendererTests : public ITestModule
{
	void ASimpleFormCanBeRendered();

public:
	void RunTests();
};