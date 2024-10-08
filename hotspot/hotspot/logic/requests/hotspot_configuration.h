#pragma once
#include "../../low_level/tcp/tcp_server.h"
#include "../input_form/ihtml_renderer.h"
#include "../input_form/iinput_form_renderer.h"
#include "../credentials/credentials_handler.h"

// TODO Rename to WifiCredentialsHotSpot

class HotSpotConfiguration : public HotSpotTcpServer
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


