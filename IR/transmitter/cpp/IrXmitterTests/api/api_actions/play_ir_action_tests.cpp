#include <memory>
#include "play_ir_action_tests.h"
#include "../../api/api_actions/play_ir_action.h"
#include "../../transmit/ir_signal_sender.h"

class MockIrSignalSender : public IIrSignalSender
{
public:
	IrCode irCodeSent;
};

static std::unique_ptr<PlayIrAction> objectUnderTest;
static std::unique_ptr<MockIrSignalSender> mockIrSignalSender;
static std::unique_ptr<IrCode> irCodeToSend;;

static PlayIrAction& CreateObjectUnderTest()
{
	mockIrSignalSender.reset(new MockIrSignalSender);
	objectUnderTest.reset(new PlayIrAction(*mockIrSignalSender.get()));
	return *objectUnderTest.get();
}

static void TheCodeDataIsRetrievedAndSentToTheWavePlayer()
{
	ApiAction& action = CreateObjectUnderTest();

	action.Action("code name");

	AssertEqual(irCodeToSend.get()->Name, mockIrSignalSender.get()->irCodeSent.Name);
}

void PlayIrActionTests::RunTests()
{
	TheCodeDataIsRetrievedAndSentToTheWavePlayer();
}

void PlayIrActionTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockIrSignalSender.release();
	irCodeToSend.release();
}
