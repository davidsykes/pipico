#pragma once
#include "../ihttp_request_router.h"
#include "ihtml_renderer.h"
#include "irenderer.h"

class SSIDPasswordInputFormRenderer : public IRenderer
{
    std::string description;
    IHtmlRenderer& html_renderer;
    IRenderer& input_form;

    virtual std::string Render();

    public:
        SSIDPasswordInputFormRenderer(
            const char* description,
            IHtmlRenderer& html_renderer,
            IRenderer& input_form) :
            description(description),
            html_renderer(html_renderer),
            input_form(input_form)
        {}
};


