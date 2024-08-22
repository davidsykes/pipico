#include <memory>
#include "logs_display_widget_tests.h"
#include "../../ir/server/widgets/log_display_widget.h"


static std::unique_ptr<MessageLogger> messageLogger;
static std::unique_ptr<LogDisplayWidget> objectUnderTest;

static LogDisplayWidget& CreateObjectUnderTest()
{
	messageLogger.reset(new MessageLogger);
	objectUnderTest.reset(new LogDisplayWidget(*messageLogger.get()));
	return *objectUnderTest.get();
}

static void TheLogsAreDisplayed()
{
	IWidget& widget = CreateObjectUnderTest();
	IMessageLogger& logger = *messageLogger.get();
	logger.Log("L1");
	logger.Log("L2");

	std::string result = widget.RenderWidget();

	AssertEqual("L1<br>L2", result);
}

void LogsDisplayWidgetTests::RunTests()
{
	TheLogsAreDisplayed();
}

void LogsDisplayWidgetTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}
