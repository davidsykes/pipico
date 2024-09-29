#include <memory>
#include "home_display_action_tests.h"
#include "../Mocks/MockApiAction.h"
#include "../../api/api_actions/home_display_action.h"
#include "../../api/formatters/button_formatter.h"
#include "../../codes/code_sequence_repository.h"

namespace
{
	class MockButtonFormatter : public IButtonFormatter
	{
		virtual std::string FormatButton(const std::string& text, const std::string& link);
	};
	class MockCodeSequenceRepository : public ICodeSequenceRepository
	{
	public:
		std::vector<CodeSequence> codeSequences;

		MockCodeSequenceRepository();
		virtual const std::vector<CodeSequence>& GetCodeSequences() { return codeSequences; }
	};
}

static std::unique_ptr<MockCodeSequenceRepository> codeSequenceRepository;
static std::unique_ptr<MockButtonFormatter> mockButtonFormatter;
static std::unique_ptr<HomeDisplayAction> objectUnderTest;

static HomeDisplayAction& CreateObjectUnderTest()
{
	codeSequenceRepository.reset(new MockCodeSequenceRepository);
	mockButtonFormatter.reset(new MockButtonFormatter);
	objectUnderTest.reset(new HomeDisplayAction(*codeSequenceRepository.get(), *mockButtonFormatter.get()));
	return *objectUnderTest.get();
}

static void HomePageDisplaysCodeSequenceButtons()
{
	ApiAction& action = CreateObjectUnderTest();

	auto result = action.Action();

	AssertEqual("Button(Sequence 1 Text,/sequence/Sequence1Name)<br>Button(Sequence 2 Text,/sequence/Sequence2Name)", result);
}

std::string MockButtonFormatter::FormatButton(const std::string& text, const std::string& link)
{
	return std::string("Button(") +  text + "," + link + ")";
}

MockCodeSequenceRepository::MockCodeSequenceRepository()
{
	CodeSequence cs1("Sequence1Name", "Sequence 1 Text");
	codeSequences.push_back(cs1);
	CodeSequence cs2("Sequence2Name", "Sequence 2 Text");
	codeSequences.push_back(cs2);
}

void HomeDisplayActionTests::RunTests()
{
	HomePageDisplaysCodeSequenceButtons();
}

void HomeDisplayActionTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockButtonFormatter.release();
	codeSequenceRepository.release();
}
