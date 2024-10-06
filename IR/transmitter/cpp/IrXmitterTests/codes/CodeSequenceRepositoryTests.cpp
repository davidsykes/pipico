#include <memory>
#include "CodeSequenceRepositoryTests.h"
#include "../../codes/code_sequence_repository.h"
#include "../../tools/message_logger.h"

static std::unique_ptr<CodeSequenceRepository> objectUnderTest;
static std::unique_ptr<MessageLogger> messageLogger;

static CodeSequenceRepository& CreateObjectUnderTest()
{
	messageLogger.reset(new MessageLogger);
	objectUnderTest.reset(new CodeSequenceRepository(*messageLogger.get()));
	return *objectUnderTest.get();
}

static void ANonExistentSequenceReturnsAnEmptySequence()
{
	ICodeSequenceRepository& repo = CreateObjectUnderTest();

	const CodeSequence& sequence = repo.GetSequence("non existent sequence");

	AssertEqual("NullSequence", sequence.Name);
	AssertEqual("Sequence Not Found", sequence.DisplayText);
}

static void ANonExistentSequenceLogsAnError()
{
	ICodeSequenceRepository& repo = CreateObjectUnderTest();

	const CodeSequence& sequence = repo.GetSequence("non existent sequence");

	AssertEqual("Sequence 'non existent sequence' not found.", messageLogger.get()->Logs()[0]);
}

static void TestForward30()
{
	ICodeSequenceRepository& repo = CreateObjectUnderTest();

	const CodeSequence& sequence = repo.GetSequence("Forward30");

	AssertEqual("Forward30", sequence.Name);
	AssertEqual("Forward 30", sequence.DisplayText);
	AssertEqual(1, sequence.Codes.size());
	AssertEqual("SonyForward", sequence.Codes[0]);
}

void CodeSequenceRepositoryTests::RunTests()
{
	ANonExistentSequenceReturnsAnEmptySequence();
	ANonExistentSequenceLogsAnError();
	TestForward30();
}

void CodeSequenceRepositoryTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	messageLogger.release();
}

