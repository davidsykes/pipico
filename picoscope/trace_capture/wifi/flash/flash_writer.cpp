#include <cstring>
#include "flash_writer.h"
#include "flash_constants.h"

uint8_t* StoreParameter(uint8_t* data_begin, uint8_t* data_current, const char* param);

FlashWriter::FlashWriter(IFlashHardware& flashHardware)
	: flashHardware(flashHardware)
{
	data_block.reset(new uint8_t[FLASH_BLOCK_SIZE]);
}

bool FlashWriter::WriteParameters(const std::vector<FlashParameter> parameters)
{
	if (parameters.size() == 0)
	{
		return true;
	}

	uint8_t* data_begin = data_block.get();
	uint8_t* data_current = data_begin;
	memcpy(data_current, FLASH_PARAMETERS_PREFIX, FLASH_PARAMETERS_PREFIX_LEN);
	data_current += FLASH_PARAMETERS_PREFIX_LEN;

	for (int x = 0; x < parameters.size(); ++x)
	{
		data_current = StoreParameter(data_begin, data_current, parameters[x].Name.c_str());
		if (data_current == 0)
		{
			return false;
		}

		data_current = StoreParameter(data_begin, data_current, parameters[x].Value.c_str());
		if (data_current == 0)
		{
			return false;
		}
	}

	*data_current = 0;

	return flashHardware.WriteFlash(data_block.get());
}


uint8_t* StoreParameter(uint8_t* data_begin, uint8_t* data_current, const char* param)
{
	size_t lengthIncludingTerminator = strlen(param) + 1;

	if (data_current + lengthIncludingTerminator >= data_begin + FLASH_BLOCK_SIZE)
	{
		return 0;
	}

	memcpy(data_current, param, lengthIncludingTerminator);
	return data_current + lengthIncludingTerminator;
}