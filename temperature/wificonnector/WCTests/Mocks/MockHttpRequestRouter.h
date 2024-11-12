#pragma once
#include "../../src/ihttp_request_router.h"

class MockRequestRouter : public IHttpRequestRouter
{
	std::string requestType;

	virtual std::string RouteHttpRequest(const char* request) { return requestType; };

public:
	MockRequestRouter(const char* type) : requestType(type) {}

	void SetResponse(const char* response) { requestType = response; }
};
