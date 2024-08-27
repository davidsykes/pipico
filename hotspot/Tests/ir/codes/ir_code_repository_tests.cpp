#include <memory>
#include "ir_code_repository_tests.h"
#include "../../ir/codes/ir_code_repository.h"
#include "../../tools/message_logger.h"

class MockRestHandler : public IRestHandler
{
	virtual std::string Get(const char* url) { return ""; }
	virtual std::string Put(const char* url, const char* body) { return ""; }
};

static std::unique_ptr<MockRestHandler> mockRestHandler;
static std::unique_ptr<MessageLogger> messageLogger;
static std::unique_ptr<IrCodeRepository> objectUnderTest;

static IrCodeRepository& CreateObjectUnderTest()
{
	mockRestHandler.reset(new MockRestHandler());
	messageLogger.reset(new MessageLogger());
	objectUnderTest.reset(new IrCodeRepository(*mockRestHandler.get()));
	return *objectUnderTest.get();
}

static void AnEmptyResponseFromTheServerResultsInNoCodesLoaded()
{
	IrCodeRepository& codes = CreateObjectUnderTest();
	codes.RetrieveCodes(*messageLogger.get());

	AssertEqual(0, codes.GetCodes().size());
}

static void AnEmptyResponseFromTheServerResultsInAnErrorBeingLogged()
{
	IrCodeRepository& codes = CreateObjectUnderTest();
	codes.RetrieveCodes(*messageLogger.get());

	IMessageLogger& logger = *messageLogger.get();
	AssertEqual(1, logger.Logs().size());
	AssertEqual("No response was received from the server when requesting IR codes", logger.Logs()[0]);
}

void IrCodeRepositoryTests::RunTests()
{
	AnEmptyResponseFromTheServerResultsInNoCodesLoaded();
	AnEmptyResponseFromTheServerResultsInAnErrorBeingLogged();
}

void IrCodeRepositoryTests::CleanUpAfterTests()
{
	mockRestHandler.release();
	messageLogger.release();
	objectUnderTest.release();
}
