#pragma once
#include <string>
#include "../../interface/system_interface.h"


constexpr auto FLASH_PAGE_SIZE = 256;
#define FLASH_CREDENTIALS_PREFIX		"CRED"
#define FLASH_CREDENTIALS_PREFIX_LEN	4

class IFlashManager
{
public:
	virtual void WriteToFlash(const std::string& SSID, const std::string& password, const std::string& error) = 0;
};

class FlashManager : public IFlashManager
{
	SYSTEM_INTERFACE_T* _systemInterface;

	virtual void WriteToFlash(const std::string& SSID, const std::string& password, const std::string& error);

public:
	FlashManager(SYSTEM_INTERFACE_T* systemInterface);
};