#include <memory>
#include "play_ir_action_tests.h"
#include "../../api/api_actions/play_ir_action.h"
#include "../../transmit/ir_signal_sender.h"
#include "../../codes/ir_codes_repository.h"

namespace
{
	class MockIrCodesRepository : public IIrCodesRepository
	{
		virtual std::vector<IrCode>& GetCodes() { Assert("Invalid"); }
		virtual IrCode* GetCode(const std::string& name);
	public:
		IrCode irCodeToSend;
	};

	class MockIrSignalSender : public IIrSignalSender
	{
		virtual void SendCode(const IrCode& code) { irCodeSent.Name = code.Name; }
	public:
		IrCode irCodeSent;
	};
}

static std::unique_ptr<PlayIrAction> objectUnderTest;
static std::unique_ptr<MockIrCodesRepository> mockIrCodesRepository;
static std::unique_ptr<MockIrSignalSender> mockIrSignalSender;
static const std::string& valid_code_name = "code name";

static void SetUpCodeRepository()
{
	mockIrCodesRepository.reset(new MockIrCodesRepository);
	mockIrCodesRepository.get()->irCodeToSend.Name = valid_code_name;
}

static PlayIrAction& CreateObjectUnderTest()
{
	SetUpCodeRepository();
	mockIrSignalSender.reset(new MockIrSignalSender);
	objectUnderTest.reset(new PlayIrAction(*mockIrSignalSender.get(), *mockIrCodesRepository.get()));
	return *objectUnderTest.get();
}

static void TheCodeDataIsRetrievedAndSentToTheWavePlayer()
{
	ApiAction& action = CreateObjectUnderTest();

	action.Action(valid_code_name);

	AssertEqual(valid_code_name, mockIrSignalSender.get()->irCodeSent.Name);
}

static void AValidCodeReturnsNoError()
{
	ApiAction& action = CreateObjectUnderTest();

	auto result = action.Action(valid_code_name);

	AssertTrue(result.empty());
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
	AValidCodeReturnsNoError();
	AnInvalidCodeReturnsAnError();
}

void PlayIrActionTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockIrCodesRepository.release();
	mockIrSignalSender.release();
}
