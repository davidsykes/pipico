#pragma once
#include "ITestModule.h"
#include "Mocks/MockCredentialsHandler.h"
#include "../configurations/hotspot_configuration.h"


class HotSpotConfigurationTests : public ITestModule
{
	Configuration* config;
	MockCredentialsHandler* mockCredentialsHandler;
	void SetUpObjectUnderTest();
	void GeneralRequestsReturnAnInputForm();
	void CredentialsSubmissionCallsCredentialsHandler();

public:
	void RunTests();
};