#include <memory>
#include "code_sequences_display_action_tests.h"
#include "../../api/api_actions/code_sequences_display_action.h"
#include "../../codes/code_sequence_repository.h"

namespace
{
	class MockButtonFormatter : public IButtonFormatter
	{
		virtual std::string FormatButton(const std::string& text, const std::string& link);
	};
	class MockCodeSequenceRepository : public ICodeSequenceRepository
	{
		virtual const std::vector<CodeSequence>& GetCodeSequences() { return codeSequences; }
		virtual const CodeSequence& GetSequence(const std::string& name) { Assert("Invalid"); }
	public:
		std::vector<CodeSequence> codeSequences;

		void AddTestSequences();
	};
}

static std::unique_ptr<MockCodeSequenceRepository> codeSequenceRepository;
static std::unique_ptr<MockButtonFormatter> mockButtonFormatter;
static std::unique_ptr<CodeSequencesDisplayAction> objectUnderTest;

static CodeSequencesDisplayAction& CreateObjectUnderTest()
{
	codeSequenceRepository.reset(new MockCodeSequenceRepository);
	mockButtonFormatter.reset(new MockButtonFormatter);
	objectUnderTest.reset(new CodeSequencesDisplayAction(
		*codeSequenceRepository.get(),
		*mockButtonFormatter.get()));
	return *objectUnderTest.get();
}

static void ActionDisplaysCodeSequenceButtons()
{
	ApiAction& action = CreateObjectUnderTest();
	codeSequenceRepository.get()->AddTestSequences();

	auto result = action.Action();

	AssertEqual("Button(Sequence 1 Text,/sequence/Sequence1Name)<br>Button(Sequence 2 Text,/sequence/Sequence2Name)", result);
}

std::string MockButtonFormatter::FormatButton(const std::string& text, const std::string& link)
{
	return std::string("Button(") +  text + "," + link + ")";
}

void MockCodeSequenceRepository::AddTestSequences()
{
	CodeSequence cs1("Sequence1Name", "Sequence 1 Text");
	codeSequences.push_back(cs1);
	CodeSequence cs2("Sequence2Name", "Sequence 2 Text");
	codeSequences.push_back(cs2);
}

void CodeSequencesDisplayActionTests::RunTests()
{
	ActionDisplaysCodeSequenceButtons();
}

void CodeSequencesDisplayActionTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockButtonFormatter.release();
	codeSequenceRepository.release();
}
