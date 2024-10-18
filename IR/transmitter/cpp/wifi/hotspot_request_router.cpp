#include "hotspot_request_router.h"

// GET /hotspot-detect.html HTTP/1.0

std::string HotSpotRequestRouter::RouteHttpRequest(const char* request)
{
	printf("HotSpotRequestRouter: %s\n", request);
	return ssidInputForm.Render();
}