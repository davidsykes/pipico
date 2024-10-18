#include <string.h>
#include "hotspot_request_router.h"

// GET /hotspot-detect.html HTTP/1.0
// GET /hotspotsubmit?ssid=a907&password=peew HTTP/1.1

std::string HotSpotRequestRouter::RouteHttpRequest(const char* request)
{
	if (strncmp(request, "CONNECT proxy-safebrowsing", 26) == 0)
	{
		return "{}";
	}

	printf("HotSpotRequestRouter: %s\n", request);
	return ssidInputForm.Render();
}