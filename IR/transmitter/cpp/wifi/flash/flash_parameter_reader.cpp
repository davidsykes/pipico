#include "flash_parameter_reader.h"
#include "flash_constants.h"

bool FlashParameterReader::ReadParameters()
{
	parameters.clear();
	flash = (const char*)flashHardware.ReadFlash();
	pointer = 0;

	if (strncmp(flash, FLASH_PARAMETERS_PREFIX, FLASH_PARAMETERS_PREFIX_LEN) != 0)
	{
		return false;
	}

	pointer = FLASH_PARAMETERS_PREFIX_LEN;
	while (!HaveWeReachedTheEndOfTheParameters())
	{
		ReadAParameter();
	}
	return pointer > 0;
}

bool FlashParameterReader::HaveWeReachedTheEndOfTheParameters()
{
	return (pointer == 0 || flash == 0 || flash[pointer] == 0);
}

std::string FlashParameterReader::ReadString()
{
	size_t end = pointer;
	while (end < FLASH_BLOCK_SIZE && flash[end] != 0)
	{
		++end;
	}
	if (end == FLASH_BLOCK_SIZE)
	{
		pointer = 0;
		return "";
	}

	const char* s = flash + pointer;
	pointer = end + 1;
	return s;
}

void FlashParameterReader::ReadAParameter()
{
	std::string name = ReadString();
	std::string value = ReadString();
	if (name.empty() || value.empty())
	{
		return;
	}
	parameters.push_back(FlashParameter(name, value));
}

bool FlashParameterReader::ContainsParameter(const std::string& name)
{
	for (int i = 0; i < parameters.size(); ++i)
	{
		if (parameters[i].Name == name)
			return true;
	}
	return false;
}

const std::string& FlashParameterReader::GetParameter(const std::string& name)
{
	for (int i = 0; i < parameters.size(); ++i)
	{
		if (parameters[i].Name == name)
			return parameters[i].Value;
	}
	return invalidParameter;
}