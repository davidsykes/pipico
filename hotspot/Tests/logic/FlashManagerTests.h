#pragma once
#include "TestFramework.h"


class FlashManagerTests : public ITestModule
{
	void BasicValuesCanBeWrittenToTheFlash();
	void IfValuesExceedSizeOfFlashPageAnErrorIsWritten();

public:
	void RunTests();
};