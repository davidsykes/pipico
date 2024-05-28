#pragma once
#include "../../logic/credentials/credentials_handler.h"

class MockCredentialsHandler : public ICredentialsHandler
{
	virtual void HandleCredentials(std::string credentials);
public:
	std::string HandledCredentials;
};