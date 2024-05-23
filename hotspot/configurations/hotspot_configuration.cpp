#include <string.h>
#include "hotspot_configuration.h"
#include "../logic/input_form/html_renderer.h"
#include "../logic/input_form/input_form_renderer.h"
#include "../logic/credentials/credentials_handler.h"

HotSpotConfiguration::HotSpotConfiguration(
    const char* description,
    IHtmlRenderer* html_renderer,
    IInputFormRenderer* input_form,
    ICredentialsHandler* credentials_handler)
{
    hotspot_description = description;
    hotspot_name = "hotspot";
    hotspot_password = "password";
    _html_renderer = html_renderer;
    if (_html_renderer == NULL) _html_renderer = new HtmlRenderer();
    _input_form = input_form;
    if (_input_form == NULL) _input_form = new InputFormRenderer();
    _credentials_handler = credentials_handler;
    if (_credentials_handler == NULL) _credentials_handler = new CredentialsHandler();
}

static bool RequestMatchesCredentialsSubmission(const char* request)
{
    return strcmp(request, "/hotspotsubmit") == 0;
}

std::string HotSpotConfiguration::process_request(const char *request, const char *params)
{
    printf("process request: '%s' '%s'\n", request, params);
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
                _html_renderer->RenderParagraph("Enter Wifi Details") +
                _input_form->Render()));

        return html;
    }
}
