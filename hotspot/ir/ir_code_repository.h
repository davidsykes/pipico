#pragma once
#include "../rest/irest_handler.h"

class IrCodeRepository
{
    IRestHandler& irRestHandler;

public:
    IrCodeRepository(IRestHandler& irRestHandler) : irRestHandler(irRestHandler) {}
    void RetrieveCodes();
};
