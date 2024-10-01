#include <memory>
#include "home_display_action_tests.h"
#include "../Mocks/MockApiAction.h"
#include "../../api/api_actions/home_display_action.h"
static std::unique_ptr<MockApiAction> sequencesDisplayAction;
static std::unique_ptr<MockApiAction> logDisplayAction;
static std::unique_ptr<HomeDisplayAction> objectUnderTest;

static HomeDisplayAction& CreateObjectUnderTest()
{
	sequencesDisplayAction.reset(new MockApiAction("Sequences"));
	logDisplayAction.reset(new MockApiAction("Logs"));
	objectUnderTest.reset(new HomeDisplayAction(
		*sequencesDisplayAction.get(),
		*logDisplayAction.get()));
	return *objectUnderTest.get();
}

static void HomePageDisplaysCodeSequenceButtonsAndLogs()
{
	ApiAction& action = CreateObjectUnderTest();

	auto result = action.Action();

	AssertEqual("SequencesLogs", result);
}

void HomeDisplayActionTests::RunTests()
{
	HomePageDisplaysCodeSequenceButtonsAndLogs();
}

void HomeDisplayActionTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	logDisplayAction.release();
	sequencesDisplayAction.release();
}
