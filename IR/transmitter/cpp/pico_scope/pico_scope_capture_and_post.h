#pragma once
#include "pico_scope.h"
#include "trace_data_formatter.h"
#include "../rest/rest_handler.h"

class IPicoScopeCaptureAndPost
{
public:
	virtual void CaptureAndPost() = 0;
};

class PicoScopeCaptureAndPost : public IPicoScopeCaptureAndPost
{
	IHardwareInterface& hw_if;
	IPicoScope& pico_scope;
	TraceDataFormatter& trace_data_formatter;
	IRestHandler& rest_handler;
	std::string trace_url;

	virtual void CaptureAndPost();
public:
	PicoScopeCaptureAndPost(
		IHardwareInterface& hw_if,
		IPicoScope& pico_scope,
		TraceDataFormatter& trace_data_formatter,
		IRestHandler& rest_handler,
		const std::string& trace_url
	)
		: hw_if(hw_if),
		pico_scope(pico_scope),
		trace_data_formatter(trace_data_formatter),
		rest_handler(rest_handler),
		trace_url(trace_url)
	{}
};
