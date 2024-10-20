#pragma once
#include "irenderer.h"
#include "../flash/flashwriter.h"

class SSIDPasswordSubmitter : public IRenderer
{
    IFlashWriter& flashWriter;

    virtual std::string Render(const std::string& param);

    void AddParameter(std::vector<FlashParameter>& flashParameters, const std::string& data);

    public:
        SSIDPasswordSubmitter(IFlashWriter& flashWriter)
            : flashWriter(flashWriter)
        {}
};


