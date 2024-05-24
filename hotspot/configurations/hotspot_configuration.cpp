#include <string.h>
#include "hotspot_configuration.h"

HotSpotConfiguration::HotSpotConfiguration(
    const char* description,
    const char* lastErrorMessage,
    IHtmlRenderer* html_renderer,
    IInputFormRenderer* input_form,
    ICredentialsHandler* credentials_handler)
{
    hotspot_description = description;
    hotspot_name = "hotspot";
    hotspot_password = "password";
    _html_renderer = html_renderer;
    _input_form = input_form;
    _credentials_handler = credentials_handler;
}

static bool RequestMatchesCredentialsSubmission(const char* request)
{
    return strcmp(request, "/hotspotsubmit") == 0;
}

std::string HotSpotConfiguration::process_request(const char *request, const char *params)
{
    printf("process request: '%s' '%s'\n---\n", request, params);
    if (RequestMatchesCredentialsSubmission(request))
    {
        _credentials_handler->HandleCredentials(params);
        return "";
    }
    else
    {
        std::string html = _html_renderer->RenderHtml(
            _html_renderer->RenderBody(
                _html_renderer->RenderHeader(hotspot_description) +
                _html_renderer->RenderParagraph("Enter WiFi Details") +
                _input_form->Render()));

        return html;
    }
}
