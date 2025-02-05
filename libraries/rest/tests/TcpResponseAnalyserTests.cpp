#include <memory>
#include <sstream>
#include "TcpResponseAnalyserTests.h"
#include "../rest/rest_handler.h"
#include "../rest/tcp_response_analyser.h"

static std::unique_ptr<TcpResponseAnalyser> objectUnderTest;

static TcpResponseAnalyser& CreateTestObject()
{
	objectUnderTest.reset(new TcpResponseAnalyser());
	return *objectUnderTest.get();
}

static std::string MakeNotOkResponse();
static std::string MakeOkResponse();
static std::string MakeHttpResponse(int status_code, const char* body);

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

	AssertEqual("Ok", body);
}

static void AValid404ResponseReturnsTheErrorCode()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();
	std::string request = MakeHttpResponse(404, "Not found");
	std::string body;

	int result = analyser.AnalyseTcpResponse(request, body);

	AssertEqual(404, result);
	AssertEqual("Not found", body);
}

static void AnInvalidHttpVersionReturnsAnErrorCode()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();
	std::string request = "HTTP/1.0 200 OK\r\n\r\n2\r\nOk\r\n0\r\n";
	std::string body;

	int result = analyser.AnalyseTcpResponse(request, body);

	AssertEqual(400, result);
}

static void LinesTerminatedByCrAreHandled()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();
	std::string request = "HTTP/1.1 200 OK\r\r2\rOk\r\r";
	std::string body;

	int result = analyser.AnalyseTcpResponse(request, body);

	AssertEqual(200, result);
	AssertEqual("Ok", body);
}

static void LinesTerminatedByLfAreHandled()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();
	std::string request = "HTTP/1.1 200 OK\n\n2\nOk\n\n";
	std::string body;

	int result = analyser.AnalyseTcpResponse(request, body);

	AssertEqual(200, result);
	AssertEqual("Ok", body);
}


static void APacketWithNoTerminatingLineFeedIsHandled()
{
	ITcpResponseAnalyser& analyser = CreateTestObject();
	std::string request = "HTTP/1.1 200 OK\r\n\r\n2\r\nOk";
	std::string body;

	int result = analyser.AnalyseTcpResponse(request, body);

	AssertEqual(200, result);
	AssertEqual("Ok", body);
}

void TcpResponseAnalyserTests::RunTests()
{
	AValid200ResponseReturnsTheStatusCode();
	AValid200ResponseReturnsTheBody();
	AValid404ResponseReturnsTheErrorCode();
	AnInvalidHttpVersionReturnsAnErrorCode();
	LinesTerminatedByCrAreHandled();
	LinesTerminatedByLfAreHandled();
	APacketWithNoTerminatingLineFeedIsHandled();
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

static std::string MakeHttpResponse(int status_code, const char* body)
{
	std::ostringstream s;

	s << "HTTP/1.1 ";
	s << status_code;

	s << """ OK\r\n\
Content - Type: text / plain; charset = utf - 8\r\n\
Date: Thu, 25 Jul 2024 06 : 28 : 24 GMT\r\n\
Server : Kestrel\r\n\
Transfer - Encoding : chunked\r\n\
\r\n";
	s << strlen(body) << "\r\n";
	s << body;
	s << "\r\n0\r\n";
	return s.str();
}