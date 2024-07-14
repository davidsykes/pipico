#include "TraceDataFormatterTests.h"
#include "../../pico_scope/pico_scope.h"

const char* prefix = "{\"type\":\"trace\",\"data\":\"";

std::string FormatTraceDataAndRemovePrefix(const PicoScopeTrace& trace);

static void TheDataBeginsWithAStandardHeader()
{
	PicoScopeTrace trace;
	trace.Reset(1);
	trace.AddChange(10);
	trace.AddChange(20);

	TraceDataFormatter formatter;

	std::string data = formatter.FormatTraceData(trace);
	data[strlen(prefix)] = 0;

	AssertEqual(prefix, data);
}

static void ASimpleTraceCanBeFormatted()
{
	PicoScopeTrace trace;
	trace.Reset(1);
	trace.AddChange(10);
	trace.AddChange(20);

	std::string data = FormatTraceDataAndRemovePrefix(trace);

	AssertEqual("78563412", data.substr(0, 8));
	AssertEqual("02000000", data.substr(8, 8));
	AssertEqual("14000000", data.substr(16, 8));
	AssertEqual("000000001", data.substr(24, 9));
	AssertEqual("0a0000000", data.substr(33, 9));
	AssertEqual("140000001", data.substr(42, 9));
	AssertEqual("\"}", data.substr(51, 2));
}

static void ATraceWithNoValuesCanBeFormatted()
{
	PicoScopeTrace trace;
	trace.Reset(1);

	const char* expected = "7856341200000000\"}";
	std::string data = FormatTraceDataAndRemovePrefix(trace);

	AssertEqual(expected, data);
}


void TraceDataFormatterTests::RunTests()
{
	TheDataBeginsWithAStandardHeader();
	ASimpleTraceCanBeFormatted();
	ATraceWithNoValuesCanBeFormatted();
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