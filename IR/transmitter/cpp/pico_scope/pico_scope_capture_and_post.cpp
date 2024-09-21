#include "pico_scope_capture_and_post.h"

void PicoScopeCaptureAndPost::CaptureAndPost()
{
	hw_if.set_led(1);
	PicoScopeTrace& trace = pico_scope.FetchTrace();
	hw_if.set_led(0);
	std::string trace_data = trace_data_formatter.FormatTraceData(trace);
	rest_handler.Put(trace_url.c_str(), trace_data.c_str());
}
