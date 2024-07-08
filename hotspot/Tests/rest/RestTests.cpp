#include <memory>
#include "RestTests.h"
#include "../../rest/rest.h"
#include "../Mocks/MockHardwareInteface.h"

class RestHardwareInterface : public IMockHardwareInterface
{
	virtual std::string tcp_request(const char* server, unsigned int port, const char* request) { this->server = server; this->port = port; data = request; return ""; };

public:
	std::string server;
	unsigned int port=0;
	std::string data;
};

static std::unique_ptr<RestHardwareInterface> hardwareInterface;
static std::unique_ptr<RestHandler> testObject;

static RestHandler& CreateTestObject()
{
	hardwareInterface.reset(new RestHardwareInterface());
	testObject.reset(new RestHandler(*hardwareInterface.get(), "server", 123));
	return *testObject.get();
}

static void PutCombinesUrlAndBody()
{
	RestHandler& rest = CreateTestObject();

	rest.Put("url", "body");

	RestHardwareInterface& hwif = *hardwareInterface.get();
	std::string data = hwif.data;
	std::string expected = "PUT url HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 4\r\n\r\nbody";

	AssertEqual(expected, data);
	AssertEqual("server", hwif.server);
	AssertEqual(123, hwif.port);
}

void RestTests::RunTests()
{
	PutCombinesUrlAndBody();
}



void RestTests::CleanUpAfterTests()
{
	hardwareInterface.release();
	testObject.release();
}
