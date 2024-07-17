#include "TraceDataFormatterTests.h"
#include "../../pico_scope/pico_scope.h"

const char* prefix = "{\"InitialValue\":11,\"values\":";

std::string FormatTraceDataAndRemovePrefix(const PicoScopeTrace& trace);

static void TheDataBeginsWithAStandardHeader()
{
	PicoScopeTrace trace;
	trace.Reset(11, 42);
	trace.AddChange(21, 10);
	trace.AddChange(34, 20);

	TraceDataFormatter formatter;

	std::string data = formatter.FormatTraceData(trace);
	data[strlen(prefix)] = 0;

	AssertEqual(prefix, data);
}

static void ASimpleTraceCanBeFormatted()
{
	PicoScopeTrace trace;
	trace.Reset(11, 42);
	trace.AddChange(21, 10);
	trace.AddChange(34, 20);

	std::string data = FormatTraceDataAndRemovePrefix(trace);

	AssertEqual("{{42,0},{21,10},{34,20}}}", data);
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