#include <cstring>
#include "flash_hardware.h"
#include "flash_program.h"

const uint8_t* FlashHardware::ReadFlash()
{
	return read_flash_data();
}