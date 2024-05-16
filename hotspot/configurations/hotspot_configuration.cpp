#include "hotspot_configuration.h"

HotSpotConfiguration::HotSpotConfiguration(IHtmlRenderer* html_renderer)
{
    _html_renderer = html_renderer;
    hotspot_name = "hotspot";
    hotspot_password = "password";
}

//#define LED_TEST_BODY "<html><body><h1>Hello from Pico W.</h1><p>Led is OFF</p><p><a href=\"?led=1\">Turn led ON</a></body></html>"

std::string HotSpotConfiguration::process_request(const char *request, const char *params)
{
    std::string html = _html_renderer->RenderHtml(
        _html_renderer->RenderBody(
            _html_renderer->RenderHeader("hello")));

    return html;
}
