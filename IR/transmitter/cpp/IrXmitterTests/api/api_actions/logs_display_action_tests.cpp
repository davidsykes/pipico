#include <memory>
#include "logs_display_action_tests.h"
#include "../../api/api_actions/log_display_action.h"


static std::unique_ptr<MessageLogger> messageLogger;
static std::unique_ptr<LogDisplayAction> objectUnderTest;

static LogDisplayAction& CreateObjectUnderTest()
{
	messageLogger.reset(new MessageLogger);
	objectUnderTest.reset(new LogDisplayAction(*messageLogger.get()));
	return *objectUnderTest.get();
}

static void TheLogsAreDisplayed()
{
	ApiAction& action = CreateObjectUnderTest();
	IMessageLogger& logger = *messageLogger.get();
	logger.Log("L1");
	logger.Log("L2");

	std::string result = action.Action();

	AssertEqual("There are 2 logs<br>\nL1<br>L2", result);
}

void LogsDisplayActionTests::RunTests()
{
	TheLogsAreDisplayed();
}

void LogsDisplayActionTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}
