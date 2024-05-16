#pragma once
#include "configuration.h"
#include "../logic/ihtml_renderer.h"

class HotSpotConfiguration : public Configuration
{
    IHtmlRenderer* _html_renderer;

    public:
        HotSpotConfiguration(IHtmlRenderer* html_renderer);
        virtual std::string process_request(const char *request, const char *params);
};


