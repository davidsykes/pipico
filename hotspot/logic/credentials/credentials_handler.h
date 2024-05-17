#pragma once
#include <string>
#include "icredentials_handler.h"

class CredentialsHandler : public ICredentialsHandler
{
public:
	virtual void HandleCredentials(std::string credentials);
};