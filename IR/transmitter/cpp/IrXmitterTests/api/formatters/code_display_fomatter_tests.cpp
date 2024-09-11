#include <memory>
#include "code_display_fomatter_tests.h"
#include "../../api/formatters/code_display_formatter.h"

static std::unique_ptr<CodeDisplayFormatter> objectUnderTest;
static std::unique_ptr<IrCode> irCode;

static CodeDisplayFormatter& CreateObjectUnderTest()
{
	objectUnderTest.reset(new CodeDisplayFormatter);
	return *objectUnderTest.get();
}

static IrCode& CreateCode()
{
	irCode.reset(new IrCode);
	irCode.get()->Name = "Code Name";
	return *irCode.get();
}

static void TheCodeHtmlIsRendered()
{
	ICodeDisplayFormatter& action = CreateObjectUnderTest();
	IrCode& code = CreateCode();

	std::string result = action.FormatCode(code);

	AssertEqual("<a href=\"/sendcode/Code Name\">Code Code Name</a>", result);
}

void CodeDisplayFormatterTests::RunTests()
{
	TheCodeHtmlIsRendered();
}

void CodeDisplayFormatterTests::CleanUpAfterTests()
{
	irCode.release();
	objectUnderTest.release();
}
