#include <memory>
#include "home_display_action_tests.h"
#include "../Mocks/MockApiAction.h"
#include "../../api/api_actions/home_display_action.h"
#include "../../api/formatters/button_formatter.h"
#include "../../codes/code_sequence_repository.h"

namespace
{
	class MockButtonFormatter : public IButtonFormatter
	{
	};
}


static std::unique_ptr<CodeSequenceRepository> codeSequenceRepository;
static std::unique_ptr<MockButtonFormatter> mockButtonFormatter;
static std::unique_ptr<HomeDisplayAction> objectUnderTest;

static HomeDisplayAction& CreateObjectUnderTest()
{
	codeSequenceRepository.reset(new CodeSequenceRepository);
	mockButtonFormatter.reset(new MockButtonFormatter);
	objectUnderTest.reset(new HomeDisplayAction(*codeSequenceRepository.get(), *mockButtonFormatter.get()));
	return *objectUnderTest.get();
}

static void HomePageDisplaysCodeSequenceButtons()
{
	ApiAction& action = CreateObjectUnderTest();

	auto result = action.Action();

	AssertEqual("Button(Code Sequence 1 text,Code Sequence 1 link)<br>Button(Code Sequence 2 text,Code Sequence 2 link)", result);
}

void HomeDisplayActionTests::RunTests()
{
	HomePageDisplaysCodeSequenceButtons();
}

void HomeDisplayActionTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockButtonFormatter.release();
	codeSequenceRepository.release();
}
