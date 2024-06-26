#pragma once
#include "configuration.h"
#include "../input_form/ihtml_renderer.h"
#include "../input_form/iinput_form_renderer.h"
#include "../credentials/credentials_handler.h"

class HotSpotConfiguration : public Configuration
{
    std::string input_form_hotspot_name;
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


