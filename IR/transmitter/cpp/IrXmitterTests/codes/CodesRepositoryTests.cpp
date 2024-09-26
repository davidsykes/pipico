#include <memory>
#include "CodesRepositoryTests.h"
#include "../../codes/ir_codes_repository.h"

static std::unique_ptr<IrCodesRepository> objectUnderTest;

static IrCodesRepository& CreateObjectUnderTest()
{
	objectUnderTest.reset(new IrCodesRepository);
	return *objectUnderTest.get();
}

static void ACodeCanBeRetrieved()
{
	IIrCodesRepository& repo = CreateObjectUnderTest();

	IrCode& code = repo.GetCodes()[0];

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

static void ACodeCanBeFoundByName()
{
	IIrCodesRepository& repo = CreateObjectUnderTest();

	IrCode* codep = repo.GetCode("testcode");
	AssertFalse(codep == 0);

	if (codep)
	{
		IrCode& code = *codep;
		AssertEqual("testcode", code.Name);
	}
}

static void IfACodeDoesNotExistGetCodeReturnsNull()
{
	IIrCodesRepository& repo = CreateObjectUnderTest();

	IrCode* code = repo.GetCode("invalid code");
	AssertTrue(code == 0);
}

static void CodeOnOffHasBeenDefined()
{
	IIrCodesRepository& repo = CreateObjectUnderTest();

	IrCode& code = *repo.GetCode("SamsungOnOff");

	AssertEqual("SamsungOnOff", code.Name);
	AssertEqual(68, code.Count);
	AssertEqual(68, code.Times.size());
	AssertEqual(0, code.Times[0]);
	AssertEqual(4538, code.Times[1]);
	AssertEqual(9026, code.Times[2]);
	AssertEqual(68, code.Values.size());
	AssertEqual(1, code.Values[0]);
	AssertEqual(0, code.Values[1]);
	AssertEqual(1, code.Values[2]);
}

void CodesRepositoryTests::RunTests()
{
	ACodeCanBeRetrieved();
	ACodeCanBeFoundByName();
	IfACodeDoesNotExistGetCodeReturnsNull();
	CodeOnOffHasBeenDefined();
}

void CodesRepositoryTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}

