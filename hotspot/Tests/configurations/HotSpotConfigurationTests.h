#pragma once
#include "TestFramework.h"
#include "Mocks/MockCredentialsHandler.h"
#include "../configurations/hotspot_configuration.h"


class HotSpotConfigurationTests : public ITestModule
{
	virtual void CleanUpAfterTests();
	//Configuration* config{};
	//MockCredentialsHandler* mockCredentialsHandler{};
	//void SetUpObjectUnderTest();
	//void GeneralRequestsReturnAnInputForm();
	//void CredentialsSubmissionCallsCredentialsHandler();

public:
	void RunTests();
};