#include <memory>
#include "TcpResponseAnalyserTests.h"
#include "../../rest/iresthandler.h"
#include "../../rest/tcpresponseanalyser.h"

static std::unique_ptr<TcpResponseAnalyser> testObject;

static TcpResponseAnalyser& CreateTestObject()
{
	testObject.reset(new TcpResponseAnalyser());
	return *testObject.get();
}

static std::string MakeNotOkResponse();
static std::string MakeOkResponse();

static void AnInvalidResponseReturnsFalse()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();

	bool result = analyser.AnalyseTcpResponse("Request", MakeNotOkResponse());

	AssertFalse(result);
}

static void AValidResponseReturnsTrue()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();

	bool result = analyser.AnalyseTcpResponse("Request", MakeOkResponse());

	AssertTrue(result);
}

void TcpResponseAnalyserTests::RunTests()
{
	AnInvalidResponseReturnsFalse();
	AValidResponseReturnsTrue();
}

void TcpResponseAnalyserTests::CleanUpAfterTests()
{
	testObject.release();
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