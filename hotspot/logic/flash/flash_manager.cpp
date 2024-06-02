#include <cstring>
#include "flash_manager.h"

FlashManager::FlashManager(IFlashHardware* flashHardware)
{
	this->flashHardware = flashHardware;
}

static size_t AddStringIfItWillFit(uint8_t* flashPage, size_t position, const std::string& s)
{
	size_t length = s.length() + 1;
	size_t new_postion = position + length;
	if (new_postion <= FLASH_PAGE_SIZE)
	{
		memcpy(flashPage + position, s.c_str(), length);
	}
	return new_postion;
}

void FlashManager::WriteToFlash(const std::string& SSID, const std::string& password, const std::string& error)
{
	uint8_t flashContents[FLASH_PAGE_SIZE];
	size_t position = 0;

	memcpy(flashContents, FLASH_CREDENTIALS_PREFIX, FLASH_CREDENTIALS_PREFIX_LEN);
	position += FLASH_CREDENTIALS_PREFIX_LEN;

	position = AddStringIfItWillFit(flashContents, position, SSID);
	position = AddStringIfItWillFit(flashContents, position, password);
	position = AddStringIfItWillFit(flashContents, position, error);

	if (position > FLASH_PAGE_SIZE)
	{
		memcpy(flashContents + FLASH_CREDENTIALS_PREFIX_LEN, "\0\0Data size error.\0", 19);
	}

	flashHardware->WriteFlash(flashContents);
}
