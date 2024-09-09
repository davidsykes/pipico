#include <memory>
#include "home_display_action_tests.h"
#include "../Mocks/MockApiAction.h"
#include "../../api/api_actions/home_display_action.h"
//

static std::unique_ptr<MockApiAction> mockHome;
static std::unique_ptr<MockApiAction> mockLogs;
static std::unique_ptr<HomeDisplayAction> objectUnderTest;

static HomeDisplayAction& CreateObjectUnderTest()
{
	mockHome.reset(new MockApiAction("Codes"));
	mockLogs.reset(new MockApiAction("Logs"));
	objectUnderTest.reset(new HomeDisplayAction(*mockHome.get(), *mockLogs.get()));
	return *objectUnderTest.get();
}

static void HomePageDisplaysCodesAndLogs()
{
	IApiAction& action = CreateObjectUnderTest();

	auto result = action.ApiAction();

	AssertEqual("Codes<br>Logs", result);
}

void HomeDisplayActionTests::RunTests()
{
	HomePageDisplaysCodesAndLogs();
}

void HomeDisplayActionTests::CleanUpAfterTests()
{
	mockHome.release();
	mockLogs.release();
	objectUnderTest.release();
}
