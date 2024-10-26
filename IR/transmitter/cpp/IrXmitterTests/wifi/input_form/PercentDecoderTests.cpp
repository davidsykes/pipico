#include <memory>
#include "TestFramework.h"
#include "PercentDecoderTests.h"
#include "../../wifi/input_form/percent_decoder.h"

static std::unique_ptr<IPercentDecoder> _decoder;

static IPercentDecoder* CreateTestObject()
{
	_decoder.reset(new PercentDecoder);
	return _decoder.get();
}

static void ASimpleValueIsUnchanged()
{
	auto decoder = CreateTestObject();

	auto result = decoder->Decode("Simple Value");

	AssertEqual(result, "Simple Value");
}

static void SpacesCanBeConverted()
{
	auto decoder = CreateTestObject();

	auto result = decoder->Decode("a%20b%20c");

	AssertEqual(result, "a b c");
}

static void AmpersandValuesCanBeConverted()
{
	auto decoder = CreateTestObject();

	auto result = decoder->Decode("a%26b%26c");

	AssertEqual(result, "a&b&c");
}

static void InvalidPercentValuesAreIgnored()
{
	auto decoder = CreateTestObject();

	auto s = "a%b%c";
	auto result = decoder->Decode(s);
	AssertEqual(result, "a%b%c");

	s = "a%b%";
	result = decoder->Decode(s);
	AssertEqual(result, "a%b%");
}

static void ExclamationMarks()
{
	auto decoder = CreateTestObject();

	auto result = decoder->Decode("Simple Value!");

	AssertEqual(result, "Simple Value!");
}

void PercentDecoderTests::RunTests()
{
	ASimpleValueIsUnchanged();
	SpacesCanBeConverted();
	AmpersandValuesCanBeConverted();
	InvalidPercentValuesAreIgnored();
	ExclamationMarks();
}

void PercentDecoderTests::CleanUpAfterTests()
{
	_decoder.release();
}

