#pragma once
#include "../../3rd_party/ihttp_response_packager.h"
#include "ihttp_request_router.h"

class HttpResponsePackager : public IHttpResponsePackager
{
	IHttpRequestRouter& requestRouter;

	virtual int RouteRequestAndPackageResponse(const char* request, std::string& header, std::string& body);

public:
	HttpResponsePackager(IHttpRequestRouter& router) : requestRouter(router) {}
};

