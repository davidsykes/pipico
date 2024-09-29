#include <memory>
#include "play_ir_sequence_action_tests.h"
#include "../../api/api_actions/play_ir_sequence_action.h"
#include "../../transmit/ir_sequence_sender.h"
#include "../../codes/code_sequence_repository.h"
#include "../Mocks/MockApiAction.h"

static const std::string& valid_sequence_name = "sequence name";

namespace
{
	class MockCodeSequenceRepository : public ICodeSequenceRepository
	{
		virtual const std::vector<CodeSequence>& GetCodeSequences() { Assert("Invalid"); }
		virtual CodeSequence& GetSequence(const std::string& name);
	public:
		MockCodeSequenceRepository() : SequenceToSend(valid_sequence_name, "link") {}

		CodeSequence SequenceToSend;
	};

	class MockIrSequenceSender : public IIrSequenceSender
	{
		virtual void SendSequence(const CodeSequence& code) { SequenceSent = code.Name; }
	public:
		std::string SequenceSent;
	};
}

static std::unique_ptr<PlayIrSequenceAction> objectUnderTest;
static std::unique_ptr<MockCodeSequenceRepository> mockCodeSequenceRepository;
static std::unique_ptr<MockIrSequenceSender> mockIrSequenceSender;
static std::unique_ptr<MockApiAction> mockApiAction;

static void SetUpSequenceRepository()
{
	mockCodeSequenceRepository.reset(new MockCodeSequenceRepository);
	mockCodeSequenceRepository.get()->SequenceToSend.Name = valid_sequence_name;
}

static PlayIrSequenceAction& CreateObjectUnderTest()
{
	SetUpSequenceRepository();
	mockIrSequenceSender.reset(new MockIrSequenceSender);
	mockApiAction.reset(new MockApiAction("Home Page"));
	objectUnderTest.reset(new PlayIrSequenceAction(
		*mockIrSequenceSender.get(),
		*mockCodeSequenceRepository.get(),
		*mockApiAction.get()));
	return *objectUnderTest.get();
}

static void TheSequenceDataIsRetrievedAndSentToTheSequencePlayer()
{
	ApiAction& action = CreateObjectUnderTest();

	action.Action(valid_sequence_name);

	AssertEqual(valid_sequence_name, mockIrSequenceSender.get()->SequenceSent);
}

static void AValidSequenceReturnsHomePageAction()
{
	ApiAction& action = CreateObjectUnderTest();

	auto result = action.Action(valid_sequence_name);

	AssertEqual("Home Page", result);
}

CodeSequence& MockCodeSequenceRepository::GetSequence(const std::string& name)
{
	if (name == valid_sequence_name)
	{
		return SequenceToSend;
	}
	Assert("Invalid");
}

void PlayIrSequenceActionTests::RunTests()
{
	TheSequenceDataIsRetrievedAndSentToTheSequencePlayer();
	AValidSequenceReturnsHomePageAction();
}

void PlayIrSequenceActionTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockCodeSequenceRepository.release();
	mockIrSequenceSender.release();
}
