#pragma once
#include "irenderer.h"
#include "../flash/flash_writer.h"
#include "percent_decoder.h"

class SSIDPasswordSubmitter : public IRenderer
{
    IFlashWriter& flashWriter;
    IPercentDecoder& percentDecoder;

    virtual std::string Render(const std::string& param);

    void AddParameter(std::vector<FlashParameter>& flashParameters, const std::string& data);

    public:
        SSIDPasswordSubmitter(IFlashWriter& flashWriter, IPercentDecoder& percentDecoder)
            : flashWriter(flashWriter),
            percentDecoder(percentDecoder)
        {}
};


