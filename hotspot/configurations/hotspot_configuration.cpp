#include "hotspot_configuration.h"
#include "../logic/html_renderer.h"
#include "../logic/input_form_renderer.h"

HotSpotConfiguration::HotSpotConfiguration(
    const char* description,
    IHtmlRenderer* html_renderer,
    IInputFormRenderer* input_form)
{
    hotspot_description = description;
    hotspot_name = "hotspot";
    hotspot_password = "password";
    _html_renderer = html_renderer;
    if (_html_renderer == NULL) _html_renderer = new HtmlRenderer();
    if (input_form == NULL)
    {
        _input_form = new InputFormRenderer();
    }
    else
    {
        _input_form = input_form;
    }
}

std::string HotSpotConfiguration::process_request(const char *request, const char *params)
{
    printf("Process Request: '%s' '%s'\n", request, params);
    std::string html = _html_renderer->RenderHtml(
        _html_renderer->RenderBody(
            _html_renderer->RenderHeader(hotspot_description) +
        _html_renderer->RenderParagraph("Enter Wifi Details") +
        _input_form->Render()));

    return html;
}
