#pragma once
#include <vector>
#include "../rest/rest_handler.h"
#include "ir_code.h"

class IrCodeRepository
{
    IRestHandler& irRestHandler;

    std::vector<IrCode> codes;

public:
    IrCodeRepository(IRestHandler& irRestHandler) : irRestHandler(irRestHandler) {}
    void RetrieveCodes();
    std::vector<IrCode>& GetCodes() { return codes; }
};
