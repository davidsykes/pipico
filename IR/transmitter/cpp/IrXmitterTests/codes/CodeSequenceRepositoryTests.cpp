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

static void TestFastForward30()
{
	ICodeSequenceRepository& repo = CreateObjectUnderTest();

	const CodeSequence& sequence = repo.GetSequence("FastForward30");

	AssertEqual("FastForward30", sequence.Name);
	AssertEqual("Forward 30", sequence.DisplayText);
	AssertEqual(1, sequence.Codes.size());
	AssertEqual("SonyForward", sequence.Codes[0]);
}

static void TestSamsungVolumeDown()
{
	ICodeSequenceRepository& repo = CreateObjectUnderTest();

	const CodeSequence& sequence = repo.GetSequence("SamsungVolumeDown");

	AssertEqual("SamsungVolumeDown", sequence.Name);
	AssertEqual("Volume Down", sequence.DisplayText);
	AssertEqual(1, sequence.Codes.size());
	AssertEqual("SamsungVolumeDown", sequence.Codes[0]);
}

static void TestSamsungVolumeUpx2()
{
	ICodeSequenceRepository& repo = CreateObjectUnderTest();

	const CodeSequence& sequence = repo.GetSequence("SamsungVolumeUpx2");

	AssertEqual("SamsungVolumeUpx2", sequence.Name);
	AssertEqual("Volume Up x 2", sequence.DisplayText);
	AssertEqual(3, sequence.Codes.size());
	AssertEqual("SamsungVolumeUp", sequence.Codes[0]);
	AssertEqual("Pause", sequence.Codes[1]);
	AssertEqual("SamsungVolumeUp", sequence.Codes[2]);
}

void CodeSequenceRepositoryTests::RunTests()
{
	ANonExistentSequenceReturnsAnEmptySequence();
	ANonExistentSequenceLogsAnError();
	TestFastForward30();
	TestSamsungVolumeDown();
	TestSamsungVolumeUpx2();
}

void CodeSequenceRepositoryTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	messageLogger.release();
}

