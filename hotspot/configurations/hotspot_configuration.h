#pragma once
#include "configuration.h"
#include "../logic/ihtml_renderer.h"

class HotSpotConfiguration : public Configuration
{
    std::string hotspot_description;
    IHtmlRenderer* _html_renderer;

    virtual std::string process_request(const char* request, const char* params);

    public:
        HotSpotConfiguration(const char* description, IHtmlRenderer* html_renderer = 0);
};


