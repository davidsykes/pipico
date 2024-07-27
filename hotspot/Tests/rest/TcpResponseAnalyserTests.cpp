#include <memory>
#include "TcpResponseAnalyserTests.h"
#include "../../rest/iresthandler.h"
#include "../../rest/tcpresponseanalyser.h"

class MockRestHandler : public IRestHandler
{
	virtual std::string Get(const char* url) { return ""; };
	virtual std::string Put(const char* url, const char* body) { return ""; };
	virtual void LogLastRequest() { logLastRequestCalled = true; }
public:
	bool logLastRequestCalled = false;
};

static std::unique_ptr<TcpResponseAnalyser> testObject;
static std::unique_ptr<MockRestHandler> mockRestHandler;

static TcpResponseAnalyser& CreateTestObject()
{
	mockRestHandler.reset(new MockRestHandler());
	testObject.reset(new TcpResponseAnalyser(*mockRestHandler.get()));
	return *testObject.get();
}

static std::string MakeNotOkResponse();
static std::string MakeOkResponse();

static void AnInvalidResponsePassesRequestAndResponseToTheLog()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();

	analyser.AnalyseTcpResponse("Request", MakeNotOkResponse());

	AssertTrue(mockRestHandler.get()->logLastRequestCalled);
}

static void AValidResponseDoesNotPassRequestAndResponseToTheLog()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();

	analyser.AnalyseTcpResponse("Request", MakeOkResponse());

	AssertFalse(mockRestHandler.get()->logLastRequestCalled);
}

void TcpResponseAnalyserTests::RunTests()
{
	AnInvalidResponsePassesRequestAndResponseToTheLog();
	AValidResponseDoesNotPassRequestAndResponseToTheLog();
}

void TcpResponseAnalyserTests::CleanUpAfterTests()
{
	testObject.release();
	mockRestHandler.release();
}

static std::string MakeNotOkResponse()
{
	return """HTTP/1.1 200 OK\
Content - Type: text / plain; charset = utf - 8\
Date: Thu, 25 Jul 2024 06 : 28 : 24 GMT\
Server : Kestrel\
Transfer - Encoding : chunked\
\
6\
Not Ok\
0\
";
}

static std::string MakeOkResponse()
{
	return """HTTP/1.1 200 OK\
Content - Type: text / plain; charset = utf - 8\
Date: Thu, 25 Jul 2024 06 : 28 : 24 GMT\
Server : Kestrel\
Transfer - Encoding : chunked\
\
6\
Not Ok\
0\
";
}