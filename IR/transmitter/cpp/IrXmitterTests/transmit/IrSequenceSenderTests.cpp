#include <memory>
#include "IrSequenceSenderTests.h"
#include "../Mocks/MockHardwareInteface.h"
#include "../../transmit/ir_code_sender.h"
#include "../../transmit/ir_sequence_sender.h"

namespace
{
	class MockCodesRepository : public IIrCodesRepository
	{
		std::vector<IrCode> _unused;
		IrCode codeBeingSent;
		virtual std::vector<IrCode>& GetCodes() { return _unused; }
		virtual IrCode* GetCode(const std::string& name) { codeBeingSent.Name = name; return &codeBeingSent; }
	public:
		std::vector<std::string> SentCodes;
	};
	class MockIrCodeSender : public IIrCodeSender
	{
		virtual void SendCode(const IrCode& code) { SentCodes.push_back(code.Name); }
	public:
		std::vector<std::string> SentCodes;
	};
}

static std::unique_ptr<IrSequenceSender> objectUnderTest;
static std::unique_ptr<MockCodesRepository> mockCodesRepository;
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
	mockCodesRepository.reset(new MockCodesRepository);
	mockIrCodeSender.reset(new MockIrCodeSender);
	objectUnderTest.reset(new IrSequenceSender(*mockCodesRepository.get(), *mockIrCodeSender.get()));
	return *objectUnderTest.get();
}

static void ASequenceIsTransmitted()
{
	IIrSequenceSender& sender = CreateTestObject();

	sender.SendSequence(*codeSequence.get());

	std::vector<std::string>& sentCodes = mockIrCodeSender.get()->SentCodes;
	AssertEqual(3, sentCodes.size());
	AssertEqual("Code 1", sentCodes[0]);
	AssertEqual("Code 2", sentCodes[1]);
	AssertEqual("Code 3", sentCodes[2]);
}


void IrSequenceSenderTests::RunTests()
{
	ASequenceIsTransmitted();
}

void IrSequenceSenderTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockCodesRepository.release();
	mockIrCodeSender.release();
	codeSequence.release();
}
