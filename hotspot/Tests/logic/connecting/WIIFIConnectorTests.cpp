#include "Assert.h"
#include "WiFiConnectorTests.h"
#include "wifi_connector.h"

class SingleAllocation
{
	void* _object;
public:
	SingleAllocation()
	{
		_object = NULL;
	}
	void Set(void* object)
	{
		delete _object;
		_object = object;
	}
	void* Value()
	{
		return _object;
	}
};

SingleAllocation systemInterface;
SingleAllocation wifiConnector;

void test1(void* object)
{
	AssertEqual("html", "<h1>contents</h1>");
}

WIFIConnectorTests::WIFIConnectorTests()
{
	RunTest(test1);
}


void* WIFIConnectorTests::SetUpObjectUnderTest()
{
	systemInterface.Set(new SYSTEM_INTERFACE_T);
	wifiConnector.Set(new WiFiConnector((SYSTEM_INTERFACE_T*)systemInterface.Value()));
	return 0;
}