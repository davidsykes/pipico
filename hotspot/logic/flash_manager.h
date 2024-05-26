#pragma once
#include <string>
#include "system_interface.h"

class IFlashManager
{
public:
	virtual void WriteToFlash(const std::string& SSID, const std::string& password) = 0;
};

class FlashManager : public IFlashManager
{
	virtual void WriteToFlash(const std::string& SSID, const std::string& password);

public:
	FlashManager(SYSTEM_INTERFACE_T* systemInterface);
};