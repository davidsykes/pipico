#include "hotspot_configuration.h"
#include "../logic/html_renderer.h"

HotSpotConfiguration::HotSpotConfiguration(const char* description, IHtmlRenderer* html_renderer)
{
    hotspot_description = description;
    hotspot_name = "hotspot";
    hotspot_password = "password";
    if (html_renderer == NULL)
    {
        _html_renderer = new HtmlRenderer();
    }
    else
    {
        _html_renderer = html_renderer;
    }
}

//#define LED_TEST_BODY "<html><body><h1>Hello from Pico W.</h1><p>Led is OFF</p><p><a href=\"?led=1\">Turn led ON</a></body></html>"

std::string HotSpotConfiguration::process_request(const char *request, const char *params)
{
    std::string html = _html_renderer->RenderHtml(
        _html_renderer->RenderBody(
            _html_renderer->RenderHeader(hotspot_description) +
        _html_renderer->RenderParagraph("Enter Wifi Details")));

    return html;
}
