#include <memory>
#include <sstream>
#include "RestTests.h"
#include "../../rest/rest.h"
#include "../Mocks/MockHardwareInteface.h"
#include <vector>

class RestHardwareInterface : public IMockHardwareInterface
{
	virtual std::string tcp_request(const char* server, unsigned int port, const char* request);

public:
	std::string server;
	unsigned int port=0;
	std::vector<std::string> sent_data;
};

static std::unique_ptr<RestHardwareInterface> hardwareInterface;
static std::unique_ptr<RestHandler> testObject;

static RestHandler& CreateTestObject()
{
	hardwareInterface.reset(new RestHardwareInterface());
	testObject.reset(new RestHandler(*hardwareInterface.get(), "server", 123));
	return *testObject.get();
}

std::string MakePutRequest(const std::string& url, const std::string& body)
{
	std::stringstream s;
	s << "PUT " << url;
	s << " HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: ";
	s << body.length() << "\r\n\r\n" << body;
	return s.str();
}

static void PutCombinesUrlAndBody()
{
	RestHandler& rest = CreateTestObject();

	rest.Put("url", "body");

	RestHardwareInterface& hwif = *hardwareInterface.get();
	std::string data = hwif.sent_data[0];
	std::string expected = MakePutRequest("url", "body");
	//std::string expected = "PUT url HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 4\r\n\r\nbody";

	AssertEqual(expected, data);
	AssertEqual("server", hwif.server);
	AssertEqual(123, hwif.port);
}

static void LogPostsLogWithLastRequestAndResponse()
{
	RestHandler& rest = CreateTestObject();

	rest.Put("url", "body");
	rest.Log();

	RestHardwareInterface& hwif = *hardwareInterface.get();
	AssertEqual(2, hwif.sent_data.size());
	std::string data = hwif.sent_data[1];
	std::string expected =
		"PUT log HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 114\r\n\r\nPUT url HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 4\r\n\r\nbody\r\n\r\nresponse";

	AssertEqual(expected, data);
}

void RestTests::RunTests()
{
	PutCombinesUrlAndBody();
	LogPostsLogWithLastRequestAndResponse();
}

std::string RestHardwareInterface::tcp_request(const char* server, unsigned int port, const char* request)
{
	this->server = server;
	this->port = port;
	sent_data.push_back(request);
	return "response";
};


void RestTests::CleanUpAfterTests()
{
	hardwareInterface.release();
	testObject.release();
}
