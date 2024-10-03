#include <memory>
#include "CodesRepositoryTests.h"
#include "../../codes/ir_codes_repository.h"
#include "../../tools/message_logger.h"

static std::unique_ptr<IrCodesRepository> objectUnderTest;
static std::unique_ptr<MessageLogger> messageLogger;

static IrCodesRepository& CreateObjectUnderTest()
{
	messageLogger.reset(new MessageLogger);
	objectUnderTest.reset(new IrCodesRepository(*messageLogger.get()));
	return *objectUnderTest.get();
}

static void ACodeCanBeFoundByName()
{
	IIrCodesRepository& repo = CreateObjectUnderTest();

	IrCode& code = *repo.GetCode("Pause");

	AssertEqual("Pause", code.Name);
	AssertEqual(2, code.Count);
	AssertEqual(2, code.Times.size());
	AssertEqual(0, code.Times[0]);
	AssertEqual(500000, code.Times[1]);
	AssertEqual(2, code.Values.size());
	AssertEqual(1, code.Values[0]);
	AssertEqual(0, code.Values[1]);
}

static void IfACodeDoesNotExistGetCodeReturnsNull()
{
	IIrCodesRepository& repo = CreateObjectUnderTest();

	IrCode* code = repo.GetCode("invalid code");
	AssertTrue(code == 0);
}

static void IfACodeDoesNotExistAMessageIsLogged()
{
	IIrCodesRepository& repo = CreateObjectUnderTest();

	IrCode* code = repo.GetCode("invalid code");

	AssertEqual("Code 'invalid code' not found.", messageLogger.get()->Logs()[0]);
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
	ACodeCanBeFoundByName();
	IfACodeDoesNotExistGetCodeReturnsNull();
	IfACodeDoesNotExistAMessageIsLogged();
	CodeOnOffHasBeenDefined();
}

void CodesRepositoryTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	messageLogger.release();
}

