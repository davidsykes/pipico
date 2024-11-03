#include "hardware_interface.h"
#include "pico/cyw43_arch.h"
#include "tusb.h"

void _initialise_pico_stdio(bool wait_for_usb_comms)
{
    stdio_init_all();
    if (wait_for_usb_comms)
    {
        while (!tud_cdc_connected()) sleep_ms(100);
    }
    printf("Stdio initialised\n");
}

int _initialise_wifi_sta(const char* ssid, const char* password)
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

void _initialise_wifi_ap(const char* ssid, const char* password)
{
    cyw43_arch_enable_ap_mode(ssid, password, CYW43_AUTH_WPA2_AES_PSK);
    printf("Ap mode started %s %s...\n", ssid, password);
}

int _cyw43_arch_init()
{
   int err = cyw43_arch_init();
    if (err) {
        printf("Wi-Fi init failed");
        return err;
    }
   return 0;
}

sHardwareInterface* create_hardware_interface()
{
    sHardwareInterface* hwif = calloc(1, sizeof(sHardwareInterface));

    hwif->initialise_pico_stdio = &_initialise_pico_stdio;
    hwif->cyw43_arch_init = &_cyw43_arch_init;
    hwif->initialise_wifi_sta = &_initialise_wifi_sta;
    hwif->initialise_wifi_ap = &_initialise_wifi_ap;

    return hwif;
}