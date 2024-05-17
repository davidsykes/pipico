#pragma once
#include "ITestModule.h"


class FormRendererTests : public ITestModule
{
	void ASimpleFormCanBeRendered();

public:
	void RunTests();
};