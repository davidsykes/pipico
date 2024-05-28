#include <memory>
#include "TestFramework.h"
#include "PercentDecoderTests.h"
#include "percent_decoder.h"

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
	AssertEqual(1, 0);
}

static void AmpersandValuesCanBeConverted()
{
	AssertEqual(1, 0);
}

void PercentDecoderTests::RunTests()
{
	ASimpleValueIsUnchanged();
	SpacesCanBeConverted();
	AmpersandValuesCanBeConverted();
}

void PercentDecoderTests::CleanUpAfterTests()
{
	_decoder.release();
}

