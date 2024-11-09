/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "tusb.h"
#include "wificonnector.h"

int main() {
    // stdio_init_all();
    
    // while (!tud_cdc_connected()) sleep_ms(100);

    // if (cyw43_arch_init()) {
    //     printf("Wi-Fi init failed");
    //     return -1;
    // }
    // printf("Create Object\n");
    WiFiConnector wiFiConnector;
//    printf("Create Object2\n");
    wiFiConnector.ConnectToWiFi("PicoTemp", "12345678");
    printf("Connected\n");

    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
    }
}
