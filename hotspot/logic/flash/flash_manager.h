#pragma once
#include <string>
#include "../../hotspot/flash_hardware.h"


#define FLASH_CREDENTIALS_PREFIX		"CRED"
#define FLASH_CREDENTIALS_PREFIX_LEN	4

class IFlashManager
{
public:
	virtual void WriteToFlash(const std::string& SSID, const std::string& password, const std::string& error) = 0;
};

class FlashManager : public IFlashManager
{
	IFlashHardware* flashHardware;

	virtual void WriteToFlash(const std::string& SSID, const std::string& password, const std::string& error);

public:
	FlashManager(IFlashHardware* flashHardware);
};