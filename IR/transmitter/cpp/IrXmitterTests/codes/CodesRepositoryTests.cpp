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
}

void CodesRepositoryTests::RunTests()
{
	ADefinitionCanBeRetrieved();
}

void CodesRepositoryTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}

