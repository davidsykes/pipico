#include "led_configuration.h"

LedConfiguration::LedConfiguration()
{
    hotspot_name = "pico_led";
    hotspot_password = "password";
}

#define LED_TEST_BODY "<html><body><h1>Hello from Pico W.</h1><p>Led is OFF</p><p><a href=\"?led=1\">Turn led ON</a></body></html>"

std::string LedConfiguration::process_request(const char *request, const char *params)
{
    return LED_TEST_BODY;
}
