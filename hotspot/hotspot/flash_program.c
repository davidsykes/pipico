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
#include "flash_program.h"

#define FLASH_TARGET_OFFSET (1256 * 1024)
#define DATA_PREFIX         "CRD1"
#define DATA_PREFIX_LEN     4
#define MAX_STRING_LENGTH   100

const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

const uint8_t* load_flash_data()
{
    return flash_target_contents;
}

int read_flash_contents(CREDENTIALS_T* credentials)
{
    if (strncmp(flash_target_contents, DATA_PREFIX, DATA_PREFIX_LEN) == 0)
    {
        credentials->hotspot_name = flash_target_contents + DATA_PREFIX_LEN;
        int mlen = strnlen(credentials->hotspot_name, MAX_STRING_LENGTH);
        if (mlen == MAX_STRING_LENGTH) return false;
        credentials->hotspot_password = credentials->hotspot_name + mlen + 1;
        mlen = strnlen(credentials->hotspot_password, MAX_STRING_LENGTH);
        if (mlen == MAX_STRING_LENGTH) return false;
        return true;
    }
    return false;
}





void print_buf(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", buf[i]);
        if (i % 16 == 15)
            printf("\n");
        else
            printf(" ");
    }
}

int flash_main() {
    printf("Flash page size: %d\n", FLASH_PAGE_SIZE);
    printf("Read original target region:\n");
    print_buf(flash_target_contents, FLASH_PAGE_SIZE);

    uint8_t random_data[FLASH_PAGE_SIZE];
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i)
        random_data[i] = i * 3; // rand() >> 16;

    printf("Generated random data:\n");
    print_buf(random_data, FLASH_PAGE_SIZE);

    // Note that a whole number of sectors must be erased at a time.
    printf("\nErasing target region...\n");
    uint32_t interrupts = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    restore_interrupts(interrupts);
    printf("Done. Read back target region:\n");
    print_buf(flash_target_contents, FLASH_PAGE_SIZE);

    printf("\nProgramming target region...\n");
    interrupts = save_and_disable_interrupts();
    flash_range_program(FLASH_TARGET_OFFSET, random_data, FLASH_PAGE_SIZE);
    restore_interrupts(interrupts);
    printf("Done. Read back target region:\n");
    print_buf(flash_target_contents, FLASH_PAGE_SIZE);

    bool mismatch = false;
    for (int i = 0; i < FLASH_PAGE_SIZE; ++i) {
        if (random_data[i] != flash_target_contents[i])
            mismatch = true;
    }
    if (mismatch)
        printf("Programming failed!\n");
    else
        printf("Programming successful!\n");
}


int try_out_flash()
{
    flash_main();
}