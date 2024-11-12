#include <memory>
#include <sstream>
#include "TestFramework.h"
#include "SSIDPasswordSubmitterTests.h"
#include "../Mocks\MockRenderer.h"
#include "../../src/input_form/ssid_password_submitter.h"

class MockFlashWriter : public IFlashWriter
{
	virtual bool WriteParameters(const std::vector<FlashParameter> parameters);
public:
	std::string DataWritten;
};

class MockPercentDecoder : public IPercentDecoder
{
	virtual std::string Decode(const std::string& value) { return "!" + value + "!"; }
};

static std::unique_ptr<MockFlashWriter> mockFlashWriter;
static std::unique_ptr<MockPercentDecoder> mockPercentDecoder;
static std::unique_ptr<SSIDPasswordSubmitter> objectUnderTest;

static SSIDPasswordSubmitter& CreateTestObject()
{
	mockFlashWriter.reset(new MockFlashWriter);
	mockPercentDecoder.reset(new MockPercentDecoder);
	objectUnderTest.reset(new SSIDPasswordSubmitter(*mockFlashWriter.get(), *mockPercentDecoder.get()));

	return *objectUnderTest.get();
}

static void TheSubmittedParametersArePercentDecodedAndPassedToTheFlashWriter()
{
	IRenderer& submitter = CreateTestObject();

	std::string result = submitter.Render("ssid=fred&password=bill");

	AssertEqual("ssid:!fred!,password:!bill!,", mockFlashWriter.get()->DataWritten);
}

static void IfTheWriterSucceedsTheSubmitterReturnsOk()
{
	IRenderer& submitter = CreateTestObject();

	std::string result = submitter.Render("ssid=fred&password=bill");

	AssertEqual("Ok", result);
}

static void DataIsTruncatedAtTheFirstSpace()
{
	IRenderer& submitter = CreateTestObject();

	std::string result = submitter.Render("ssid=fred&password=bill more request data");

	AssertEqual("ssid:!fred!,password:!bill!,", mockFlashWriter.get()->DataWritten);
}

static void ParametersWithoutEqualSignsAreIgnored()
{
	IRenderer& submitter = CreateTestObject();

	std::string result = submitter.Render("one=1&two&three=3");

	AssertEqual("one:!1!,three:!3!,", mockFlashWriter.get()->DataWritten);
}

static void IfNoParametersAreSuppliedTheSubmitterReturnsNotOk()
{
	IRenderer& submitter = CreateTestObject();

	std::string result = submitter.Render("");

	AssertEqual("Fail", result);
}

static void IfNoParametersAreFoundTheSubmitterReturnsNotOk()
{
	IRenderer& submitter = CreateTestObject();

	std::string result = submitter.Render("a&b&c");

	AssertEqual("Fail", result);
}

bool MockFlashWriter::WriteParameters(const std::vector<FlashParameter> parameters)
{
	std::ostringstream s;
	for (int i = 0; i < parameters.size(); ++i)
	{
		s << parameters[i].Name << ":" << parameters[i].Value << ",";
	}
	DataWritten = s.str();
	return false;
}

void SSIDPasswordSubmitterTests::RunTests()
{
	TheSubmittedParametersArePercentDecodedAndPassedToTheFlashWriter();
	IfTheWriterSucceedsTheSubmitterReturnsOk();
	DataIsTruncatedAtTheFirstSpace();
	ParametersWithoutEqualSignsAreIgnored();
	IfNoParametersAreSuppliedTheSubmitterReturnsNotOk();
	IfNoParametersAreFoundTheSubmitterReturnsNotOk();
}

void SSIDPasswordSubmitterTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockFlashWriter.release();
	mockPercentDecoder.release();
}
