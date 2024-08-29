#pragma once
#include <vector>
#include "ir_code.h"
#include "../tools/message_logger.h"

class IrCodeRepository
{
    std::vector<IrCode> codes;

public:
    std::vector<IrCode>& GetCodes() { return codes; }
};
