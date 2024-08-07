#include <memory>
#include "ir_code_repository_tests.h"
#include "../../ir/codes/ir_code_repository.h"

class MockRestHandler : public IRestHandler
{
	virtual std::string Get(const char* url) { return ""; }
	virtual std::string Put(const char* url, const char* body) { return ""; }
};

static std::unique_ptr<MockRestHandler> mockRestHandler;
static std::unique_ptr<IrCodeRepository> objectUnderTest;

static IrCodeRepository& CreateObjectUnderTest()
{
	mockRestHandler.reset(new MockRestHandler());
	objectUnderTest.reset(new IrCodeRepository(*mockRestHandler.get()));
	return *objectUnderTest.get();
}

static void AnEmptyResponseFromTheServerResultsInNoCodesLoaded()
{
	IrCodeRepository& codes = CreateObjectUnderTest();
	codes.RetrieveCodes();

	AssertEqual(0, codes.GetCodes().size());
}

void IrCodeRepositoryTests::RunTests()
{
	AnEmptyResponseFromTheServerResultsInNoCodesLoaded();
}

void IrCodeRepositoryTests::CleanUpAfterTests()
{
	mockRestHandler.release();
	objectUnderTest.release();
}
