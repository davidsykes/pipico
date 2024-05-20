#pragma once
#include "configuration.h"
#include "../logic/input_form/ihtml_renderer.h"
#include "../logic/input_form/iinput_form_renderer.h"
#include "../logic/credentials/icredentials_handler.h"

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
            IHtmlRenderer* html_renderer = 0,
            IInputFormRenderer* input_form=0,
            ICredentialsHandler* credentials_handler=0);
};


