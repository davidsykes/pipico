#pragma once
#include <string>

class ICredentialsHandler
{
public:
	virtual void HandleCredentials(std::string credentials) = 0;
};