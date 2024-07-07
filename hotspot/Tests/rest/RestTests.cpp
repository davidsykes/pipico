#include <memory>
#include "RestTests.h"
#include "../../rest/rest.h"
#include "../Mocks/MockHardwareInteface.h"

class RestHardwareInterface : public IMockHardwareInterface
{

	virtual std::string tcp_request(const char* request) { data = request; return ""; };

public:
	std::string data;
};

static std::unique_ptr<RestHardwareInterface> hardwareInterface;
static std::unique_ptr<RestHandler> testObject;

static RestHandler& CreateTestObject()
{
	hardwareInterface.reset(new RestHardwareInterface());
	testObject.reset(new RestHandler(*hardwareInterface.get()));
	return *testObject.get();
}

static void PutCombinesUrlAndBody()
{
	RestHandler& rest = CreateTestObject();

	rest.Put("url", "body");

	std::string data = hardwareInterface.get()->data;
	std::string expected = "PUT url HTTP/1.1\r\nHost: ir.api\r\nAccept: */*\r\n\r\nbody";
	AssertEqual(expected, data);
}

void RestTests::RunTests()
{
	PutCombinesUrlAndBody();
}



void RestTests::CleanUpAfterTests()
{
	hardwareInterface.release();
	testObject.release();
}
