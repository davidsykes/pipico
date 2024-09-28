#include <memory>
#include "button_formatter_tests.h"
#include "../../api/formatters/button_formatter.h"

static std::unique_ptr<ButtonFormatter> objectUnderTest;

static ButtonFormatter& CreateObjectUnderTest()
{
	objectUnderTest.reset(new ButtonFormatter);
	return *objectUnderTest.get();
}


static void TheButtonIsRendered()
{
	IButtonFormatter& action = CreateObjectUnderTest();

	std::string result = action.FormatButton("text", "link");

	AssertEqual("<a href=\"link\"><button>text</button></a>", result);
}

void ButtonFormatterTests::RunTests()
{
	TheButtonIsRendered();
}

void ButtonFormatterTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}
