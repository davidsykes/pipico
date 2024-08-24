#include <memory>
#include "TcpRequestMakerTests.h"
#include "../../rest/tcp_request_maker.h"
#include "../../rest/tcp_response_analyser.h"
//#include "../../tools/message_logger.h"
#include "../Mocks/MockHardwareInteface.h"

class RequestMakerHardwareInterface : public IMockHardwareInterface
{
	virtual int tcp_request(const char* server, unsigned int port, const char* request, std::string& response)
	{
		Server = server;
		Port = port;
		RequestMade = request;
		response = Response;
		return ReturnCode;
	}

public:
	std::string Server;
	unsigned int Port=0;
	std::string RequestMade;
	std::string Response;
	int ReturnCode = -87;
};

class MockTcpResponseAnalyser : public ITcpResponseAnalyser
{
	virtual bool AnalyseTcpResponse(const std::string& server_response, std::string& analysed_response);

public:
	std::string server_response;
	std::string analysed_response;
	bool analyse_result = true;
};

static std::unique_ptr<TcpRequestMaker> objectUnderTest;
static std::unique_ptr<RequestMakerHardwareInterface> mockHardwareInterface;
//static std::unique_ptr<MessageLogger> messageLogger;
static std::unique_ptr<MockTcpResponseAnalyser> mockTcpResponseAnalyser;
//
static ITcpRequestMaker& CreateTestObject()
{
	mockHardwareInterface.reset(new RequestMakerHardwareInterface());
	mockTcpResponseAnalyser.reset(new MockTcpResponseAnalyser());
	//	messageLogger.reset(new MessageLogger);
	objectUnderTest.reset(new TcpRequestMaker(
		"Server ip",
		4242,
		*mockHardwareInterface.get(),
		*mockTcpResponseAnalyser.get()));
	TcpRequestMaker* m = objectUnderTest.get();
	TcpRequestMaker& p = *m;
	ITcpRequestMaker& i = p;
	return i;
}
 
static void TheRequestIsPassedToTheServer()
{
	auto& maker = CreateTestObject();

	std::string response;
	maker.MakeRequest("Request", response);

	AssertEqual("Server ip", mockHardwareInterface.get()->Server);
	AssertEqual(4242, mockHardwareInterface.get()->Port);
	AssertEqual("Request", mockHardwareInterface.get()->RequestMade);
}

static void TheResponseIsPassedToTheTcpResponseAnalyser()
{
	auto& maker = CreateTestObject();
	mockHardwareInterface.get()->Response = "Server Response";

	std::string response;
	maker.MakeRequest("Request", response);

	AssertEqual("Analysed Response", response);
}

static void TheHttpStatusCodeIsReturned() { AssertEqual("a", "b"); }
static void IfAServerErrorOccursAnAppropritateCodeIsReturned() { AssertEqual("a", "b"); }
static void IfAnErrorOccursTheErrorIsLogged() { AssertEqual("a", "b"); }
static void IfTheResponseIsNotRecognisedAnErrorIsReturned() { AssertEqual("a", "b"); }

//static std::string MakePutRequest(const std::string& url, const std::string& body)
//{
//	std::stringstream s;
//	s << "PUT " << url;
//	s << " HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: ";
//	s << body.length() << "\r\n\r\n" << body;
//	return s.str();
//}
//
//static void GetReturnsServerResponse()
//{
//	IRestHandler& rest = CreateTestObject();
//
//	std::string result = rest.Get("url");
//
//	AssertEqual("url response", result);
//}
//
//static void GetErrorsAreLogged()
//{
//	IRestHandler& rest = CreateTestObject();
//
//	std::string result = rest.Get("url");
//
//	AssertEqual("", result);
//	IMessageLogger& ml = *messageLogger.get();
//	AssertEqual(1, ml.Logs().size());
//	AssertEqual("1", ml.Logs()[0]);
//}
//
//static void PutCombinesUrlAndBody()
//{
//	IRestHandler& rest = CreateTestObject();
//
//	rest.Put("url", "body");
//
//	RestHardwareInterface& hwif = *mockHardwareInterface.get();
//	std::string data = hwif.sent_data[0];
//	std::string expected = MakePutRequest("url", "body");
//
//	AssertEqual(expected, data);
//	AssertEqual("server", hwif.server);
//	AssertEqual(123, hwif.port);
//}
//
//static void PutPassesRequestAndResponseToTCPResponseAnalyser()
//{
//	IRestHandler& rest = CreateTestObject();
//
//	rest.Put("url", "body");
//
//	RestHardwareInterface& hwif = *mockHardwareInterface.get();
//	std::string data = hwif.sent_data[0];
//	std::string expected = MakePutRequest("url", "body");
//
//	AssertEqual(expected, mockTcpResponseAnalyser.get()->request);
//	AssertEqual("response", mockTcpResponseAnalyser.get()->response);
//}
//
//static void PutLogsTheLastRequestIfTheAnalyserReturnsFalse()
//{
//	IRestHandler& rest = CreateTestObject();
//	mockTcpResponseAnalyser.get()->analyse_result = false;
//
//	rest.Put("url", "body");
//
//	RestHardwareInterface& hwif = *mockHardwareInterface.get();
//	AssertEqual(2, hwif.sent_data.size());
//	std::string data = hwif.sent_data[1];
//	std::string expected =
//		"PUT /log HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 114\r\n\r\nPUT url HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 4\r\n\r\nbody\r\n\r\nresponse";
//
//	AssertEqual(expected, data);
//}

bool MockTcpResponseAnalyser::AnalyseTcpResponse(const std::string& server_response, std::string& analysed_response)
{
	if (server_response == "Server Response")
	{
		analysed_response = "Analysed Response";
		return true;
	}
	return false;
}

void TcpRequestMakerTests::RunTests()
{
	TheRequestIsPassedToTheServer();
	TheResponseIsPassedToTheTcpResponseAnalyser();

	TheHttpStatusCodeIsReturned();
	IfAServerErrorOccursAnAppropritateCodeIsReturned();
	IfAnErrorOccursTheErrorIsLogged();
	IfTheResponseIsNotRecognisedAnErrorIsReturned();
}

//std::string RestHardwareInterface::tcp_request(const char* server, unsigned int port, const char* request)
//{
//	this->server = server;
//	this->port = port;
//	sent_data.push_back(request);
//	return "response";
//};
//

void TcpRequestMakerTests::CleanUpAfterTests()
{
	mockHardwareInterface.release();
//	messageLogger.release();
	mockTcpResponseAnalyser.release();
	objectUnderTest.release();
}
