#include <memory>
#include "play_ir_code_action_tests.h"
#include "../../api/api_actions/play_ir_code_action.h"
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

static std::unique_ptr<PlayIrCodeAction> objectUnderTest;
static std::unique_ptr<MockIrCodesRepository> mockIrCodesRepository;
static std::unique_ptr<MockIrCodeSender> mockIrCodeSender;
static std::unique_ptr<MockApiAction> mockApiAction;
static const std::string& valid_sequence_name = "code name";

static void SetUpCodeRepository()
{
	mockIrCodesRepository.reset(new MockIrCodesRepository);
	mockIrCodesRepository.get()->irCodeToSend.Name = valid_sequence_name;
}

static PlayIrCodeAction& CreateObjectUnderTest()
{
	SetUpCodeRepository();
	mockIrCodeSender.reset(new MockIrCodeSender);
	mockApiAction.reset(new MockApiAction("Home Page"));
	objectUnderTest.reset(new PlayIrCodeAction(
		*mockIrCodeSender.get(),
		*mockIrCodesRepository.get(),
		*mockApiAction.get()));
	return *objectUnderTest.get();
}

static void TheCodeDataIsRetrievedAndSentToTheWavePlayer()
{
	ApiAction& action = CreateObjectUnderTest();

	action.Action(valid_sequence_name);

	AssertEqual(valid_sequence_name, mockIrCodeSender.get()->irCodeSent.Name);
}

static void AValidCodeReturnsHomePageAction()
{
	ApiAction& action = CreateObjectUnderTest();

	auto result = action.Action(valid_sequence_name);

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
	if (name == valid_sequence_name)
	{
		return &irCodeToSend;
	}
	return 0;
}

void PlayIrCodeActionTests::RunTests()
{
	TheCodeDataIsRetrievedAndSentToTheWavePlayer();
	AValidCodeReturnsHomePageAction();
	AnInvalidCodeReturnsAnError();
}

void PlayIrCodeActionTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockIrCodesRepository.release();
	mockIrCodeSender.release();
}
