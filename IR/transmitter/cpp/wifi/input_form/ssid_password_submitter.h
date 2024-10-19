#pragma once
#include "irenderer.h"

class SSIDPasswordSubmitter : public IRenderer
{

    virtual std::string Render();

    public:
        SSIDPasswordSubmitter()
        {}
};


