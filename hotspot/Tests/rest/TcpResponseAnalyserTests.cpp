#include <memory>
#include "TcpResponseAnalyserTests.h"
#include "../../rest/rest_handler.h"
#include "../../rest/tcp_response_analyser.h"

static std::unique_ptr<TcpResponseAnalyser> objectUnderTest;

static TcpResponseAnalyser& CreateTestObject()
{
	objectUnderTest.reset(new TcpResponseAnalyser());
	return *objectUnderTest.get();
}

static std::string MakeNotOkResponse();
static std::string MakeOkResponse();

static void AValid200ResponseReturnsTheStatusCode()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();

	std::string body;
	int result = analyser.AnalyseTcpResponse(MakeOkResponse(), body);

	AssertEqual(200, result);
}

static void AValid200ResponseReturnsTheBody()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();

	std::string body;
	int result = analyser.AnalyseTcpResponse(MakeOkResponse(), body);

	AssertEqual("200", body);
}

static void AnInvalidResponseReturnsFalse()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();

	std::string body;
	bool result = analyser.AnalyseTcpResponse(MakeNotOkResponse(), body);

	AssertFalse(result);
}

void TcpResponseAnalyserTests::RunTests()
{
	AValid200ResponseReturnsTheStatusCode();
	AValid200ResponseReturnsTheBody();
	AnInvalidResponseReturnsFalse();
}

void TcpResponseAnalyserTests::CleanUpAfterTests()
{
	objectUnderTest.release();
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