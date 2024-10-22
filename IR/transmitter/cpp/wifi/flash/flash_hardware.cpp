#include <cstdint>
#include "../../low_level/flash_program.h"
#include "flash_hardware.h"


const uint8_t* FlashHardware::ReadFlash()
{
	return read_flash_data();
}

bool FlashHardware::WriteFlash(const uint8_t* data)
{
	return write_flash_data(data);
}