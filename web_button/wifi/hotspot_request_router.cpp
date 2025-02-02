#include <string.h>
#include "hotspot_request_router.h"

//#define DEBUG_REQUESTS

std::string HotSpotRequestRouter::RouteHttpRequest(const char* request)
{
#ifdef DEBUG_REQUESTS
	printf("vvvv REQUEST vvvv\n%s\n^^^^^^^^^^^^^^^^^\n", request);
#endif
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

