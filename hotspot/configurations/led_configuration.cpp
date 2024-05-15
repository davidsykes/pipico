#include "led_configuration.h"

LedConfiguration::LedConfiguration()
{
    hotspot_name = "pico_led";
    hotspot_password = "password";
}

#define LED_TEST_BODY "<html><body><h1>Hello from Pico W.</h1><p>Led is %s</p><p><a href=\"?led=%d\">Turn led %s</a></body></html>"

std::string LedConfiguration::process_request(const char *request, const char *params)
{
    return "Hello led";
}
