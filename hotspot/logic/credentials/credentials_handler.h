#pragma once
#include <string>
#include "percent_decoder.h"
#include "../flash/flash_manager.h"

class ICredentialsHandler
{
public:
	virtual void HandleCredentials(std::string credentials) = 0;
};

class CredentialsHandler : public ICredentialsHandler
{
	IPercentDecoder* _percentDecoder;
	IFlashManager* _flashManager;

	void ConvertAndWriteCredentials(const std::string& SSID, const std::string& password);
	void WriteCredentials(const std::string& SSID, const std::string& password);
	void SetError(const std::string& error);

public:
	CredentialsHandler(IPercentDecoder* percentDecoder, IFlashManager* flashManager);

	virtual void HandleCredentials(std::string credentials);
};