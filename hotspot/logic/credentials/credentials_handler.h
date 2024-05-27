#pragma once
#include <string>
#include "icredentials_handler.h"
#include "system_interface.h"
#include "percent_decoder.h"
#include "../interface/flash_manager.h"

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