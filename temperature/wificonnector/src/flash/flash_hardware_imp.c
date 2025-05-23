/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include <string.h>
#include "hardware/flash.h"
#include "hardware/sync.h"
#include "flash_hardware_imp.h"

#define FLASH_TARGET_OFFSET (1856 * 1024)
#define DATA_PREFIX         "CRD1"
#define DATA_PREFIX_LEN     4
#define MAX_STRING_LENGTH   100

//#define DEBUG_FLASH_WRITING
#ifdef DEBUG_FLASH_WRITING
#define DEBUG_printf printf
#endif

const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

const uint8_t* read_flash_data()
{
    return flash_target_contents;
}

#ifdef DEBUG_FLASH_WRITING
void print_buf(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", buf[i]);
        if (i % 16 == 15)
            printf("\n");
        else
            printf(" ");
    }
}
#endif

int write_flash_data(const uint8_t* flash_data)
{
    //flash_test();
#ifdef DEBUG_FLASH_WRITING
    printf("Read current values\n");
    print_buf(flash_target_contents, FLASH_PAGE_SIZE);
#endif
    printf("\nErasing target region...%d / %d\n", FLASH_SECTOR_SIZE, FLASH_PAGE_SIZE);
    uint32_t interrupts = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    restore_interrupts(interrupts);

    printf("\nProgramming target region %d...\n", FLASH_TARGET_OFFSET);
#ifdef DEBUG_FLASH_WRITING
    print_buf(flash_data, FLASH_PAGE_SIZE);
#endif
    interrupts = save_and_disable_interrupts();
    flash_range_program(FLASH_TARGET_OFFSET, flash_data, FLASH_PAGE_SIZE);
    restore_interrupts(interrupts);
    printf("Done. Read back target region:\n");
#ifdef DEBUG_FLASH_WRITING
    print_buf(flash_target_contents, FLASH_PAGE_SIZE);
#endif
    bool mismatch = false;
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i) {
        if (flash_data[i] != flash_target_contents[i])
            mismatch = true;
    }
    if (mismatch)
        printf("Programming failed!\n");
    else
        printf("Programming successful!\n");
    return (!mismatch);
}
