#include <memory>
#include "TcpRequestMakerTests.h"
#include "../rest/tcp_request_maker.h"

class MockPicoTcpClient : public IPicoTcpClient
{
public:
	std::string Server;
	int Port = 0;
	std::string RequestMade;
	std::string Response = "Server Response";
	int TcpRequestReturnCode = 0;

private:
	int tcp_request(const char* server, unsigned int port, const char* request, std::string& response)
	{
		Server = server;
		Port = port;
		RequestMade = request;
		response = Response;
		return TcpRequestReturnCode;
	}
};

class MockTcpResponseAnalyser : public ITcpResponseAnalyser
{
	virtual int AnalyseTcpResponse(const std::string& server_response, std::string& analysed_response);

public:
	std::string server_response;
	std::string analysed_response;
	int status_code = -1;
};

class MockTcpRequestErrorLogger : public ITcpRequestErrorLogger
{
	virtual void LogError(int error, const std::string& server, int port, const std::string& request, const std::string& response)
	{ Server = server, Port = port, Error = error; Request = request; Response = response; }
public:
	int Error = -77;
	std::string Server;
	int Port = 0;
	std::string Request;
	std::string Response;
};

static std::unique_ptr<TcpRequestMaker> objectUnderTest;
static std::unique_ptr<MockPicoTcpClient> mockPicoTcpClient;
static std::unique_ptr<MockTcpRequestErrorLogger> mockTcpRequestErrorLogger;
static std::unique_ptr<MockTcpResponseAnalyser> mockTcpResponseAnalyser;

static ITcpRequestMaker& CreateTestObject()
{
	mockPicoTcpClient.reset(new MockPicoTcpClient());
	mockTcpResponseAnalyser.reset(new MockTcpResponseAnalyser());
	mockTcpRequestErrorLogger.reset(new MockTcpRequestErrorLogger);
	objectUnderTest.reset(new TcpRequestMaker(
		"Server ip",
		4242,
		*mockPicoTcpClient.get(),
		*mockTcpResponseAnalyser.get(),
		*mockTcpRequestErrorLogger.get()));
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

	AssertEqual("Server ip", mockPicoTcpClient.get()->Server);
	AssertEqual(4242, mockPicoTcpClient.get()->Port);
	AssertEqual("Request", mockPicoTcpClient.get()->RequestMade);
}

static void TheResponseIsPassedToTheTcpResponseAnalyser()
{
	auto& maker = CreateTestObject();

	std::string response;
	maker.MakeRequest("Request", response);

	AssertEqual("Analysed Response", response);
}

static void TheHttpStatusCodeIsReturned()
{
	auto& maker = CreateTestObject();
	mockTcpResponseAnalyser.get()->status_code = 2020;

	std::string response;
	int status = maker.MakeRequest("Request", response);

	AssertEqual(2020, status);
}

static void IfAServerErrorOccursAnAppropriateCodeIsReturned()
{
	auto& maker = CreateTestObject();
	mockPicoTcpClient.get()->TcpRequestReturnCode = -14;

	std::string response;
	int status = maker.MakeRequest("Request", response);

	AssertEqual("tcp error -14", response);
	AssertEqual(500, status);
}

static void IfAnErrorOccursTheErrorIsLogged()
{
	auto& maker = CreateTestObject();
	mockPicoTcpClient.get()->TcpRequestReturnCode = -14;

	std::string response;
	int status = maker.MakeRequest("Request", response);

	AssertEqual(-14, mockTcpRequestErrorLogger.get()->Error);
	AssertEqual("Server ip", mockTcpRequestErrorLogger.get()->Server);
	AssertEqual(4242, mockTcpRequestErrorLogger.get()->Port);
	AssertEqual("Request", mockTcpRequestErrorLogger.get()->Request);
	AssertEqual("Server Response", mockTcpRequestErrorLogger.get()->Response);
}

static void IfTheResponseIsNotRecognisedAnErrorIsReturned()
{
	auto& maker = CreateTestObject();
	mockTcpResponseAnalyser.get()->status_code = 142;

	std::string response;
	int status = maker.MakeRequest("Request", response);

	AssertEqual(status, 142);
}

int MockTcpResponseAnalyser::AnalyseTcpResponse(const std::string& server_response, std::string& analysed_response)
{
	if (server_response == "Server Response")
	{
		analysed_response = "Analysed Response";
		return status_code;
	}
	return -46;
}

void TcpRequestMakerTests::RunTests()
{
	TheRequestIsPassedToTheServer();
	TheResponseIsPassedToTheTcpResponseAnalyser();

	TheHttpStatusCodeIsReturned();
	IfAServerErrorOccursAnAppropriateCodeIsReturned();
	IfAnErrorOccursTheErrorIsLogged();
	IfTheResponseIsNotRecognisedAnErrorIsReturned();
}

void TcpRequestMakerTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockPicoTcpClient.release();
	mockTcpRequestErrorLogger.release();
	mockTcpResponseAnalyser.release();
}
