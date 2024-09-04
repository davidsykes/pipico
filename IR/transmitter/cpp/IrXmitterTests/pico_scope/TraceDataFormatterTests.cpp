#include "TraceDataFormatterTests.h"
#include "../../pico_scope/pico_scope.h"

const char* prefix = "{\"InitialValue\":11,\"Values\":";

std::string FormatTraceDataAndRemovePrefix(const PicoScopeTrace& trace);

static void TheDataBeginsWithAStandardHeader()
{
	PicoScopeTrace trace;
	trace.Reset(11, 42);
	trace.AddChange(10, 21);
	trace.AddChange(20, 34);

	TraceDataFormatter formatter;

	std::string data = formatter.FormatTraceData(trace);
	data[strlen(prefix)] = 0;

	AssertEqual(prefix, data);
}

static void ASimpleTraceCanBeFormatted()
{
	PicoScopeTrace trace;
	trace.Reset(11, 42);
	trace.AddChange(10, 21);
	trace.AddChange(20, 34);

	std::string data = FormatTraceDataAndRemovePrefix(trace);

	AssertEqual("[[0,42],[10,21],[20,34]]}", data);
}


void TraceDataFormatterTests::RunTests()
{
	TheDataBeginsWithAStandardHeader();
	ASimpleTraceCanBeFormatted();
}
void TraceDataFormatterTests::CleanUpAfterTests()
{
}

std::string FormatTraceDataAndRemovePrefix(const PicoScopeTrace& trace)
{
	TraceDataFormatter formatter;
	std::string fullTrace = formatter.FormatTraceData(trace);
	AssertTrue(fullTrace.size() > strlen(prefix));
	return fullTrace.substr(strlen(prefix));
}