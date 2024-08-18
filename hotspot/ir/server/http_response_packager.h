#pragma once
#include "../../3rd_party/ihttp_response_packager.h"
#include "ihttp_request_handler.h"

class HttpResponsePackager : public IHttpResponsePackager
{
	IHttpRequestHandler& requestRouter;

	virtual int RouteRequestAndPackageResponse(const char* request, std::string& header, std::string& body);

public:
	HttpResponsePackager(IHttpRequestHandler& router) : requestRouter(router) {}
};

