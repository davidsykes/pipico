#include <memory>
#include "MessageLoggerTests.h"
#include "message_logger.h"
#include "system_interface.h"

static std::unique_ptr<SYSTEM_INTERFACE_T> systemInterface;
static uint8_t flashContents[FLASH_PAGE_SIZE];
static std::unique_ptr<IMessageLogger> messageLogger;

static void write_flash_data(const uint8_t* data)
{
	memcpy(flashContents, data, FLASH_PAGE_SIZE);
}

static const uint8_t* read_flash_data()
{
	return flashContents;
}

static IMessageLogger* CreateTestObject()
{
	systemInterface.reset(new SYSTEM_INTERFACE_T);
	systemInterface.get()->read_flash_data = &read_flash_data;
	systemInterface.get()->write_flash_data = &write_flash_data;
	messageLogger.reset(new MessageLogger(systemInterface.get()));
	return messageLogger.get();
}

static void WhenThereIsNoDataThereAreNoLogs()
{
	auto logger = CreateTestObject();

	auto logs = logger->GetLogs();

	AssertEqual(0, logs.size());
}

static void AMessageCanBeLogged()
{
	auto logger = CreateTestObject();

	logger->Log("Log Message");

	auto logs = logger->GetLogs();
	AssertEqual(1, logs.size());
	AssertEqual("Log Message", logs[0]);
}

static void MultipleMessagesCanBeLogged()
{
	auto logger = CreateTestObject();

	logger->Log("Message 1");
	logger->Log("Message 2");
	logger->Log("Message 3");

	auto logs = logger->GetLogs();
	AssertEqual(3, logs.size());
	AssertEqual("Message 1", logs[0]);
	AssertEqual("Message 2", logs[1]);
	AssertEqual("Message 3", logs[2]);
}

void MessageLoggerTests::RunTests()
{
	//WhenThereIsNoDataThereAreNoLogs();
	//AMessageCanBeLogged();
	//MultipleMessagesCanBeLogged();
}


void MessageLoggerTests::CleanUpAfterTests()
{
	systemInterface.release();
	messageLogger.release();
}