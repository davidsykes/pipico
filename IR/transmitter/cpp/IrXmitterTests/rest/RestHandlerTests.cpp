#include <memory>
#include "RestHandlerTests.h"
#include "../../rest/rest_handler.h"

class RestMockTcpRequestMaker : public ITcpRequestMaker
{
	virtual int MakeRequest(const std::string& request, std::string& response);

public:
	std::string Request;
	std::string Response = "Tcp Request Response";
	int StatusCode = 33;
};

static std::unique_ptr<RestHandler> objectUnderTest;
static std::unique_ptr<RestMockTcpRequestMaker> mockTcpRequestMaker;

static IRestHandler& CreateTestObject()
{
	mockTcpRequestMaker.reset(new RestMockTcpRequestMaker);
	objectUnderTest.reset(new RestHandler(*mockTcpRequestMaker.get()));
	return *objectUnderTest.get();
}

static void GetPassesAGetRequestToTheTcpRequestMaker()
{
	auto& rest = CreateTestObject();

	rest.Get("get url");

	AssertEqual("GET get url", mockTcpRequestMaker.get()->Request);
}

static void GetReturnsTheTcpRequestMakerResponse()
{
	auto& rest = CreateTestObject();

	auto response = rest.Get("get url");

	AssertEqual("Tcp Request Response", response);
}

static void PutPassesAGetRequestToTheTcpRequestMaker()
{
	auto& rest = CreateTestObject();

	rest.Put("put url", "put body");

	const char* expected = "PUT put url HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 8\r\n\r\nput body";
	AssertEqual(expected, mockTcpRequestMaker.get()->Request);
}

static void PutReturnsTheTcpRequestMakerResponse()
{
	auto& rest = CreateTestObject();

	auto response = rest.Put("put url", "put body");

	AssertEqual("Tcp Request Response", response);
}

int RestMockTcpRequestMaker::MakeRequest(const std::string& request, std::string& response)
{
	Request = request;
	response = Response;
	return StatusCode;
}

void RestHandlerTests::RunTests()
{
	GetPassesAGetRequestToTheTcpRequestMaker();
	GetReturnsTheTcpRequestMakerResponse();
	PutPassesAGetRequestToTheTcpRequestMaker();
	PutReturnsTheTcpRequestMakerResponse();
}

void RestHandlerTests::CleanUpAfterTests()
{
	mockTcpRequestMaker.release();
	objectUnderTest.release();
}
