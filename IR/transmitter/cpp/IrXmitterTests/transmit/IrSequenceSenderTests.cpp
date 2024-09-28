#include <memory>
#include "IrSequenceSenderTests.h"
#include "../Mocks/MockHardwareInteface.h"
#include "../../transmit/ir_code_sender.h"
#include "../../transmit/ir_sequence_sender.h"

namespace
{
	class MockIrCodeSender : public IIrCodeSender
	{
		virtual void SendCode(const IrCode& code) { SentCodes.push_back(code.Name); }
	public:
		std::vector<std::string> SentCodes;
	};
}

static std::unique_ptr<IrSequenceSender> objectUnderTest;
static std::unique_ptr<MockIrCodeSender> mockIrCodeSender;
static std::unique_ptr<CodeSequence> codeSequence;

static void CreateData()
{
	codeSequence.reset(new CodeSequence("Test Sequence"));
	codeSequence.get()->Codes.push_back("Code 1");
	codeSequence.get()->Codes.push_back("Code 2");
	codeSequence.get()->Codes.push_back("Code 3");
}

static IrSequenceSender& CreateTestObject()
{
	CreateData();
	mockIrCodeSender.reset(new MockIrCodeSender);
	objectUnderTest.reset(new IrSequenceSender(*mockIrCodeSender.get()));
	return *objectUnderTest.get();
}

static void ASequenceIsTransmitted()
{
	IIrSequenceSender& sender = CreateTestObject();

	sender.SendSequence(*codeSequence.get());

	AssertEqual(1, 2);
}


void IrSequenceSenderTests::RunTests()
{
	ASequenceIsTransmitted();
}

void IrSequenceSenderTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockIrCodeSender.release();
	codeSequence.release();
}
