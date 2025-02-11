#include <cstdio>
#include <string>
#include "pico/cyw43_arch.h"
#include "tusb.h"
#include "../rest/rest_library.h"
#include "ssid.txt"

#define JB_IP   "192.168.1.126"
#define JB_PORT 5002

int main()
{
    stdio_init_all();
    while (!tud_cdc_connected()) sleep_ms(100);
    printf("Stdio initialised..\n");

    int err = cyw43_arch_init();
    if (err) {
        printf("Wi-Fi init failed");
        return err;
    }

    printf("Connect to Wi-Fi %s %s...\n", WIFI_SSID, WIFI_PASSWORD);
    cyw43_arch_enable_sta_mode();
    printf("Connecting to Wi-Fi %s %s...\n", WIFI_SSID, WIFI_PASSWORD);
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 20000))
    {
        printf("failed to connect to %s.\n", WIFI_SSID);
        return 1;
    }
    printf("Connected.\n");


    RestLibrary rest_library(JB_IP, JB_PORT);
    IRestHandler& rest(rest_library);


    std::string response = rest.Get("/PlayCollection/7");
    printf(response.c_str());

    printf("Ended..\n");
}