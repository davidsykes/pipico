#include <stdio.h>
#include "system_interface.h"
#include "flash_program.h"

void SetUpSystemInterface(SYSTEM_INTERFACE_T* systemInterface)
{
    systemInterface->read_flash_data = &read_flash_data;
    systemInterface->write_flash_data = &write_flash_data;
}