#include <memory>
#include "raw_display_action_tests.h"
#include "../Mocks/MockApiAction.h"
#include "../../api/api_actions/raw_display_action.h"
//

static std::unique_ptr<MockApiAction> mockHome;
static std::unique_ptr<MockApiAction> mockLogs;
static std::unique_ptr<RawDisplayAction> objectUnderTest;

static RawDisplayAction& CreateObjectUnderTest()
{
	mockHome.reset(new MockApiAction("Codes"));
	mockLogs.reset(new MockApiAction("Logs"));
	objectUnderTest.reset(new RawDisplayAction(*mockHome.get(), *mockLogs.get()));
	return *objectUnderTest.get();
}

static void HomePageDisplaysCodesAndLogs()
{
	ApiAction& action = CreateObjectUnderTest();

	auto result = action.Action();

	AssertEqual("Codes<br>Logs", result);
}

void RawDisplayActionTests::RunTests()
{
	HomePageDisplaysCodesAndLogs();
}

void RawDisplayActionTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockHome.release();
	mockLogs.release();
}
