#include "hardware_interface.h"
#include "pico/cyw43_arch.h"
#include "tusb.h"
#include "picow_tcp_client.h"


void _initialise_pico_stdio()
{
    stdio_init_all();
    while (!tud_cdc_connected()) sleep_ms(100);
    printf("Stdio initialised\n");
}

int _initialise_wifi(const char* ssid, const char* password)
{

    stdio_init_all();
    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi %s %s...\n", ssid, password);
    if (cyw43_arch_wifi_connect_blocking(ssid, password, CYW43_AUTH_WPA2_AES_PSK)) {
        printf("failed to connect.\n");
        return 1;
    } else {
        printf("Connected.\n");
    }
    return 0;
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

uint64_t _get_time_us()
{
    return time_us_64();
}

void _initialise_input_pin(int pin_number)
{
     gpio_init(pin_number);
     gpio_set_dir(pin_number, GPIO_IN);
}

void _gpio_set_pull_up(int pin_number, int value)
{
    if (value == 0)
    {
        gpio_pull_down(pin_number);
    }
    else
    {
        gpio_pull_up(pin_number);
    }
}

void _initialise_output_pin(int pin_number)
{
     gpio_init(pin_number);
     gpio_set_dir(pin_number, GPIO_OUT);
}

int _gpio_get(int pin_number)
{
    return gpio_get(pin_number);
}

int _get_pins()
{
    return gpio_get_all();
}

int _wait_pins_change(sPinsChangeData* pins_change_data, int mask, uint64_t timeout)
{
    while (true)
    {
        int value = _get_pins() & mask;
        uint64_t now = time_us_64();
        if ( value != pins_change_data->current_value)
        {
            pins_change_data->new_value = value;
            pins_change_data->time_us = now;
            return 1;
        }
        if ((now - pins_change_data->time_us) >= timeout)
        {
            return 0;
        }
    }
}

void _gpio_put(int pin_number, int value)
{
    gpio_put(pin_number, value);
}

void _set_led(int value)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, value);
}

void _sleep_us(int useconds)
{
    sleep_us(useconds);
}

int _tcp_request(const char* server_ip,
                         uint port,
                         const char* request,
                         char*result,
                         int max_result_length)
{
    return run_tcp_client_test(server_ip,
                         port,
                         request,
                         result,
                         max_result_length);
}

void _cyw43_arch_deinit()
{
    cyw43_arch_deinit();
}

sHardwareInterface* create_hardware_interface()
{
    sHardwareInterface* hwif = calloc(1, sizeof(sHardwareInterface));

    hwif->initialise_pico_stdio = &_initialise_pico_stdio;
    hwif->cyw43_arch_init = &_cyw43_arch_init;
    hwif->initialise_wifi = &_initialise_wifi;
    hwif->get_time_us = &_get_time_us;
    hwif->initialise_input_pin = &_initialise_input_pin;
    hwif->gpio_set_pull_up = &_gpio_set_pull_up;
    hwif->initialise_output_pin = &_initialise_output_pin;
    hwif->gpio_get = &_gpio_get;
    hwif->get_pins = &_get_pins;
    hwif->wait_pins_change = &_wait_pins_change;
    hwif->gpio_put = &_gpio_put;
    hwif->set_led = &_set_led;
    hwif->sleep_us = &_sleep_us;
    hwif->tcp_request = &_tcp_request;
    hwif->cyw43_arch_deinit = &_cyw43_arch_deinit;

    return hwif;
}