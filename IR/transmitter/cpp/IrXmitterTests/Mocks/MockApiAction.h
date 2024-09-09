#pragma once
#include "../../api/api_actions/iapi_action.h"


//class MockRequestHandler : public IApiAction
//{
//	std::string requestType;
//
//	virtual std::string ApiAction() { return requestType; };
//
//public:
//	MockRequestHandler(const char* type) : requestType(type) {}
//};
//

class MockApiAction : public IApiAction
{
	std::string requestType;

	virtual std::string ApiAction() { return requestType; };

public:
	MockApiAction(const char* type) : requestType(type) {}
};
