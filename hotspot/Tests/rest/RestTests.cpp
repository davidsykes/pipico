#include <memory>
#include <sstream>
#include "RestTests.h"
#include "../../rest/resthandler.h"
#include "../../rest/itcpresponseanalyser.h"
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

class MockTcpResponseAnalyser : public ITcpResponseAnalyser
{
	virtual void AnalyseTcpResponse(const std::string& request, const std::string& response) { this->request = request; this->response = response; }
public:
	std::string request;
	std::string response;
};

static std::unique_ptr<RestHandler> testObject;
static std::unique_ptr<RestHardwareInterface> mockHardwareInterface;
static std::unique_ptr<MockTcpResponseAnalyser> mockTcpResponseAnalyser;

static RestHandler& CreateTestObject()
{
	mockHardwareInterface.reset(new RestHardwareInterface());
	mockTcpResponseAnalyser.reset(new MockTcpResponseAnalyser());
	testObject.reset(new RestHandler(*mockHardwareInterface.get(), *mockTcpResponseAnalyser.get(), "server", 123));
	return *testObject.get();
}

static std::string MakePutRequest(const std::string& url, const std::string& body)
{
	std::stringstream s;
	s << "PUT " << url;
	s << " HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: ";
	s << body.length() << "\r\n\r\n" << body;
	return s.str();
}

static void PutCombinesUrlAndBody()
{
	IRestHandler& rest = CreateTestObject();

	rest.Put("url", "body");

	RestHardwareInterface& hwif = *mockHardwareInterface.get();
	std::string data = hwif.sent_data[0];
	std::string expected = MakePutRequest("url", "body");

	AssertEqual(expected, data);
	AssertEqual("server", hwif.server);
	AssertEqual(123, hwif.port);
}

static void PutPassesRequestAndResponseToTCPResponseAnalyser()
{
	IRestHandler& rest = CreateTestObject();

	rest.Put("url", "body");

	RestHardwareInterface& hwif = *mockHardwareInterface.get();
	std::string data = hwif.sent_data[0];
	std::string expected = MakePutRequest("url", "body");

	AssertEqual(expected, mockTcpResponseAnalyser.get()->request);
	AssertEqual("response", mockTcpResponseAnalyser.get()->response);
}

static void LogPostsLogWithLastRequestAndResponse()
{
	IRestHandler& rest = CreateTestObject();

	rest.Put("url", "body");
	rest.LogLastRequest();

	RestHardwareInterface& hwif = *mockHardwareInterface.get();
	AssertEqual(2, hwif.sent_data.size());
	std::string data = hwif.sent_data[1];
	std::string expected =
		"PUT /log HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 114\r\n\r\nPUT url HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 4\r\n\r\nbody\r\n\r\nresponse";

	AssertEqual(expected, data);
}

void RestTests::RunTests()
{
	PutCombinesUrlAndBody();
	PutPassesRequestAndResponseToTCPResponseAnalyser();
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
	mockHardwareInterface.release();
	testObject.release();
}
