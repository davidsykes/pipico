#include <memory>
#include "CodeSequenceRepositoryTests.h"
#include "../../codes/code_sequence_repository.h"

static std::unique_ptr<CodeSequenceRepository> objectUnderTest;

static CodeSequenceRepository& CreateObjectUnderTest()
{
	objectUnderTest.reset(new CodeSequenceRepository);
	return *objectUnderTest.get();
}

static void TestNonExistentSequence()
{
	CodeSequenceRepository& repo = CreateObjectUnderTest();

	const CodeSequence& sequence = repo.GetSequence("non existent sequence");

	AssertEqual("Sequence not found", sequence.Name);
	AssertEqual("Sequence not found", sequence.DisplayText);
	AssertEqual(0, sequence.Codes.size());
}

static void TestFastForward30()
{
	CodeSequenceRepository& repo = CreateObjectUnderTest();

	const CodeSequence& sequence = repo.GetSequence("FastForward30");

	AssertEqual("FastForward30", sequence.Name);
	AssertEqual("Forward 30", sequence.DisplayText);
	AssertEqual(1, sequence.Codes.size());
	AssertEqual("SonyForward", sequence.Codes[0]);
}

static void TestSamsungVolumeDown()
{
	CodeSequenceRepository& repo = CreateObjectUnderTest();

	const CodeSequence& sequence = repo.GetSequence("SamsungVolumeDown");

	AssertEqual("SamsungVolumeDown", sequence.Name);
	AssertEqual("Volume Down", sequence.DisplayText);
	AssertEqual(1, sequence.Codes.size());
	AssertEqual("SamsungVolumeDown", sequence.Codes[0]);
}

void CodeSequenceRepositoryTests::RunTests()
{
	TestNonExistentSequence();
	TestFastForward30();
	TestSamsungVolumeDown();
}

void CodeSequenceRepositoryTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}

