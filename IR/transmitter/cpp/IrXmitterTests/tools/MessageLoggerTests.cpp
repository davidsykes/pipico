#include <memory>
#include "MessageLoggerTests.h"
#include "../../tools/message_logger.h"

static std::unique_ptr<MessageLogger> objectUnderTest;

static MessageLogger& CreateTestObject()
{
	objectUnderTest.reset(new MessageLogger);
	return *objectUnderTest.get();
}

static void ASimpleMessageCanBeLogged()
{
	IMessageLogger& log = CreateTestObject();

	log.Log("Hello World");

	AssertEqual(1, log.Logs().size());
	AssertEqual("Hello World", log.Logs()[0]);
}

static void SeveralMessagesCanBeLogged()
{
	IMessageLogger& log = CreateTestObject();

	log.Log("Hello World1");
	log.Log("Hello World2");
	log.Log("Hello World3");

	AssertEqual(3, log.Logs().size());
	AssertEqual("Hello World1", log.Logs()[0]);
	AssertEqual("Hello World2", log.Logs()[1]);
	AssertEqual("Hello World3", log.Logs()[2]);
}

void MessageLoggerTests::RunTests()
{
	ASimpleMessageCanBeLogged();
	SeveralMessagesCanBeLogged();
}

void MessageLoggerTests::CleanUpAfterTests()
{
	objectUnderTest.release();
}
