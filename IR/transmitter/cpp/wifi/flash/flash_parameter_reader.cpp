#include "flash_parameter_reader.h"

#define FLASH_PARAMETERS_PREFIX		"xyzzy"
#define FLASH_PARAMETERS_PREFIX_LEN	5

void FlashParameterReader::ReadParameters()
{
	parameters.clear();
	flash = (const char* )flashHardware.ReadFlash();
	pointer = 0;

	//if (strncmp(flash, FLASH_PARAMETERS_PREFIX, FLASH_PARAMETERS_PREFIX_LEN) == 0)
	{
		pointer = FLASH_PARAMETERS_PREFIX_LEN;
		while (!HaveWeReachedTheEndOfTheParameters())
		{
			ReadAParameter();
		}
	}
}

bool FlashParameterReader::HaveWeReachedTheEndOfTheParameters()
{
	return (pointer == 0 || flash == 0 || flash[pointer] == 0);
}

std::string FlashParameterReader::ReadString()
{
	// if (!HaveWeReachedTheEndOfTheParameters)
	const char* s = flash + pointer;
	size_t len = strlen(s);
	// if s >
	pointer = pointer + len + 1;
	return s;
}

void FlashParameterReader::ReadAParameter()
{
	std::string name = ReadString();
	std::string value = ReadString();
//	if (name.empty() || value.empty())
//		return;

	parameters.push_back(FlashParameter(name, value));
}

bool FlashParameterReader::ContainsParameter(const std::string& name)
{
	return false;
}

const std::string& FlashParameterReader::GetParameter(const std::string& name)
{
	return "glgl";
}