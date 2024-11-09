#include "wifi_hardware_interface.h"
#include "pico/cyw43_arch.h"
#include "tusb.h"

WiFiHardwareInterface::WiFiHardwareInterface()
{
   int err = cyw43_arch_init();
    if (err) {
        printf("Wi-Fi init failed");
    }
}

void WiFiHardwareInterface::initialise_pico_stdio(bool wait_for_usb_comms)
{
    stdio_init_all();
    if (wait_for_usb_comms)
    {
        while (!tud_cdc_connected()) sleep_ms(100);
    }
    printf("Stdio initialised\n");
}

int WiFiHardwareInterface::initialise_wifi_sta(const char* ssid, const char* password)
{
    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi %s %s...\n", ssid, password);
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 20000)) {
        printf("failed to connect to %s.\n", ssid);
        return 1;
    } else {
        printf("Connected.\n");
    }
    return 0;
}

void WiFiHardwareInterface::initialise_wifi_ap(const char* ssid, const char* password)
{
    cyw43_arch_enable_ap_mode(ssid, password, CYW43_AUTH_WPA2_AES_PSK);
    printf("Ap mode started %s %s...\n", ssid, password);
}
