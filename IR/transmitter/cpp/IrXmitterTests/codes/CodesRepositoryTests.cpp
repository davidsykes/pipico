#include <memory>
#include "CodesRepositoryTests.h"
#include "../../codes/ir_codes_repository.h"

static std::unique_ptr<IrCodesRepository> objectUnderTest;

static IrCodesRepository& CreateObjectUnderTest()
{
	objectUnderTest.reset(new IrCodesRepository);
	return *objectUnderTest.get();
}

static void ADefinitionCanBeRetrieved()
{
	IIrCodesRepository& definitions = CreateObjectUnderTest();

	auto code = definitions.First();

	AssertEqual("testcode", code.Name);
	AssertEqual(68, code.Count);
	AssertEqual(68, code.Times.size());
	AssertEqual(0, code.Times[0]);
	AssertEqual(4509, code.Times[1]);
	AssertEqual(9024, code.Times[2]);
	AssertEqual(68, code.Values.size());
	AssertEqual(1, code.Values[0]);
	AssertEqual(0, code.Values[1]);
	AssertEqual(1, code.Values[2]);
}

void CodesRepositoryTests::RunTests()
{
	ADefinitionCanBeRetrieved();
}

void CodesRepositoryTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}

