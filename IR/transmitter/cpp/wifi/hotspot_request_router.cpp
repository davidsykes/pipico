#include <string.h>
#include "hotspot_request_router.h"

// GET /hotspot-detect.html HTTP/1.0

std::string HotSpotRequestRouter::RouteHttpRequest(const char* request)
{
	if (strncmp(request, "CONNECT proxy-safebrowsing", 26) == 0)
	{
		return "{}";
	}

	if (strncmp(request, "GET /hotspotsubmit?", 19) == 0)
	{
		return hotspotsubmit.Render(request + 19);
	}

	printf("HotSpotRequestRouter: %s\n", request);
	return ssidInputForm.Render();
}
