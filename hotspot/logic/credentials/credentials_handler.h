#pragma once
#include <string>
#include "icredentials_handler.h"
#include "system_interface.h"
#include "percent_decoder.h"
#include "flash_manager.h"

class CredentialsHandler : public ICredentialsHandler
{
	IPercentDecoder* _percentDecoder;
	IFlashManager* _flashManager;


	void ConvertAndWriteCredentials(const std::string& SSID, const std::string& password);
	void WriteCredentials(const std::string& SSID, const std::string& password);

public:
	CredentialsHandler(IPercentDecoder* percentDecoder, IFlashManager* flashManager);

	virtual void HandleCredentials(std::string credentials);
};