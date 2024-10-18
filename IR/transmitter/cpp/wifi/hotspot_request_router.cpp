#include "hotspot_request_router.h"

std::string HotSpotRequestRouter::RouteHttpRequest(const char* request)
{
	return ssidInputForm.Render();
}