#include <memory>
#include "TcpResponseAnalyserTests.h"
#include "../../rest/irest_handler.h"
#include "../../rest/tcp_response_analyser.h"

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
	return """HTTP/1.1 200 OK\r\n\
Content - Type: text / plain; charset = utf - 8\r\n\
Date: Thu, 25 Jul 2024 06 : 28 : 24 GMT\r\n\
Server : Kestrel\r\n\
Transfer - Encoding : chunked\r\n\
\r\n\
6\r\n\
Not Ok\r\n\
0\r\n\
";
}

static std::string MakeOkResponse()
{
	return """HTTP/1.1 200 OK\r\n\
Content - Type: text / plain; charset = utf - 8\r\n\
Date: Sat, 27 Jul 2024 06 : 24 : 40 GMT\r\n\
Server : Kestrel\r\n\
Transfer - Encoding : chunked\r\n\
\r\n\
2\r\n\
Ok\r\n\
0\r\n\
";
}