#pragma once
#include <vector>
#include "../rest/rest_handler.h"
#include "ir_code.h"
#include "../../tools/message_logger.h"

class IrCodeRepository
{
    IRestHandler& irRestHandler;

    std::vector<IrCode> codes;

public:
    IrCodeRepository(IRestHandler& irRestHandler) : irRestHandler(irRestHandler) {}
    void RetrieveCodes(IMessageLogger& messageLogger);
    std::vector<IrCode>& GetCodes() { return codes; }
};
