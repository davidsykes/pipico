#include <memory>
#include "codes_display_action_tests.h"
#include "../Mocks/MockApiAction.h"
#include "../../api/api_actions/codes_display_action.h"

class MockIrCodesRepository : public IIrCodesRepository
{
	std::vector<IrCode> codes;

	virtual std::vector<IrCode>& GetCodes() { return codes; }
};

class MockCodeDisplayFormatter : public ICodeDisplayFormatter
{
	virtual std::string FormatCode(const IrCode& code) { return code.Name; }
};

static std::unique_ptr<CodesDisplayAction> objectUnderTest;
static std::unique_ptr<MockIrCodesRepository> mockIrCodesRepository;
static std::unique_ptr<MockCodeDisplayFormatter> mockCodeDisplayFormatter;

static MockIrCodesRepository* CreateIrCodesRepository()
{
	MockIrCodesRepository* repop = new MockIrCodesRepository();
	IIrCodesRepository& repo = *repop;

	IrCode code1;
	code1.Name = "Code 1";
	repo.GetCodes().push_back(std::move(code1));
	IrCode code2;
	code2.Name = "Code 2";
	repo.GetCodes().push_back(std::move(code2));

	return repop;
}

static CodesDisplayAction& CreateObjectUnderTest()
{
	mockIrCodesRepository.reset(CreateIrCodesRepository());
	mockCodeDisplayFormatter.reset(new MockCodeDisplayFormatter);
	objectUnderTest.reset(new CodesDisplayAction(*mockIrCodesRepository.get(),
		*mockCodeDisplayFormatter.get()));
	return *objectUnderTest.get();
}

static void TheCodesDisplayPageDisplaysAllOfTheDefinedCodes()
{
	IApiAction& action = CreateObjectUnderTest();

	std::string result = action.ApiAction();

	AssertEqual("Code 1<br>Code 2<br>", result);
}

void CodesDisplayActionTests::RunTests()
{
	TheCodesDisplayPageDisplaysAllOfTheDefinedCodes();
}

void CodesDisplayActionTests::CleanUpAfterTests()
{
	mockIrCodesRepository.release();
	mockCodeDisplayFormatter.release();
	objectUnderTest.release();
}
