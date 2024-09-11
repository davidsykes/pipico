#pragma once
#include "../../api/api_actions/api_action.h"

class MockApiAction : public ApiAction
{
	std::string requestType;

	virtual std::string Action() { return requestType; };
	virtual std::string Action(const std::string& p) { return requestType + " " + p; };

public:
	MockApiAction(const char* type) : requestType(type) {}
};
