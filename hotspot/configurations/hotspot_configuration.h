#pragma once
#include "configuration.h"
#include "../logic/input_form/ihtml_renderer.h"
#include "../logic/input_form/iinput_form_renderer.h"
#include "../logic/credentials/credentials_handler.h"

class HotSpotConfiguration : public Configuration
{
    std::string hotspot_description;
    IHtmlRenderer* _html_renderer;
    IInputFormRenderer* _input_form;
    ICredentialsHandler* _credentials_handler;

    virtual std::string process_request(const char* request, const char* params);

    public:
        HotSpotConfiguration(
            const char* description,
            const char* lastErrorMessage,
            IHtmlRenderer* html_renderer,
            IInputFormRenderer* input_form,
            ICredentialsHandler* credentials_handler);
};


