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
		virtual IrCode* GetCode(const std::string& name);
	public:
		std::vector<std::string> ValidCodes;
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
	codeSequence.reset(new CodeSequence("Test Sequence", "Test Sequence"));
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
	mockCodesRepository.get()->ValidCodes.push_back("Code 1");
	mockCodesRepository.get()->ValidCodes.push_back("Code 2");
	mockCodesRepository.get()->ValidCodes.push_back("Code 3");

	sender.SendSequence(*codeSequence.get());

	std::vector<std::string>& sentCodes = mockIrCodeSender.get()->SentCodes;
	AssertEqual(3, sentCodes.size());
	AssertEqual("Code 1", sentCodes[0]);
	AssertEqual("Code 2", sentCodes[1]);
	AssertEqual("Code 3", sentCodes[2]);
}

static void IfACodeIsNotFoundItIsSkipped()
{
	IIrSequenceSender& sender = CreateTestObject();
	mockCodesRepository.get()->ValidCodes.push_back("Code 1");
	mockCodesRepository.get()->ValidCodes.push_back("Code 3");

	sender.SendSequence(*codeSequence.get());

	std::vector<std::string>& sentCodes = mockIrCodeSender.get()->SentCodes;
	AssertEqual(2, sentCodes.size());
	AssertEqual("Code 1", sentCodes[0]);
	AssertEqual("Code 3", sentCodes[1]);
}

IrCode* MockCodesRepository::GetCode(const std::string& name)
{
	codeBeingSent.Name = name;
	for (int i = 0; i < ValidCodes.size(); ++i)
	{
		if (name == ValidCodes[i])
			return &codeBeingSent;
	}
	return 0;
}

void IrSequenceSenderTests::RunTests()
{
	ASequenceIsTransmitted();
	IfACodeIsNotFoundItIsSkipped();
}

void IrSequenceSenderTests::CleanUpAfterTests()
{
	objectUnderTest.release();
	mockCodesRepository.release();
	mockIrCodeSender.release();
	codeSequence.release();
}
