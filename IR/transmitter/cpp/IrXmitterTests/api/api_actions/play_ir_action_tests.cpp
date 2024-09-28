#include <memory>
#include "play_ir_action_tests.h"
#include "../../api/api_actions/play_ir_action.h"
#include "../../transmit/ir_code_sender.h"
#include "../../codes/ir_codes_repository.h"
#include "../Mocks/MockApiAction.h"

namespace
{
	class MockIrCodesRepository : public IIrCodesRepository
	{
		virtual std::vector<IrCode>& GetCodes() { Assert("Invalid"); }
		virtual IrCode* GetCode(const std::string& name);
	public:
		IrCode irCodeToSend;
	};

	class MockIrCodeSender : public IIrCodeSender
	{
		virtual void SendCode(const IrCode& code) { irCodeSent.Name = code.Name; }
	public:
		IrCode irCodeSent;
	};
}

static std::unique_ptr<PlayIrAction> objectUnderTest;
static std::unique_ptr<MockIrCodesRepository> mockIrCodesRepository;
static std::unique_ptr<MockIrCodeSender> mockIrCodeSender;
static std::unique_ptr<MockApiAction> mockApiAction;
static const std::string& valid_code_name = "code name";

static void SetUpCodeRepository()
{
	mockIrCodesRepository.reset(new MockIrCodesRepository);
	mockIrCodesRepository.get()->irCodeToSend.Name = valid_code_name;
}

static PlayIrAction& CreateObjectUnderTest()
{
	SetUpCodeRepository();
	mockIrCodeSender.reset(new MockIrCodeSender);
	mockApiAction.reset(new MockApiAction("Home Page"));
	objectUnderTest.reset(new PlayIrAction(
		*mockIrCodeSender.get(),
		*mockIrCodesRepository.get(),
		*mockApiAction.get()));
	return *objectUnderTest.get();
}

static void TheCodeDataIsRetrievedAndSentToTheWavePlayer()
{
	ApiAction& action = CreateObjectUnderTest();

	action.Action(valid_code_name);

	AssertEqual(valid_code_name, mockIrCodeSender.get()->irCodeSent.Name);
}

static void AValidCodeReturnsHomePageAction()
{
	ApiAction& action = CreateObjectUnderTest();

	auto result = action.Action(valid_code_name);

	AssertEqual("Home Page", result);
}

static void AnInvalidCodeReturnsAnError()
{
	ApiAction& action = CreateObjectUnderTest();

	auto result = action.Action("invalid code name");

	AssertEqual("Code invalid code name not found", result);
}

IrCode* MockIrCodesRepository::GetCode(const std::string& name)
{
	if (name == valid_code_name)
	{
		return &irCodeToSend;
	}
	return 0;
}

void PlayIrActionTests::RunTests()
{
	TheCodeDataIsRetrievedAndSentToTheWavePlayer();
	AValidCodeReturnsHomePageAction();
	AnInvalidCodeReturnsAnError();
}

void PlayIrActionTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockIrCodesRepository.release();
	mockIrCodeSender.release();
}
