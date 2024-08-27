#include "stdio.h"
#include "ir_code_repository.h"

void IrCodeRepository::RetrieveCodes(IMessageLogger& messageLogger)
{
    printf("Retrieve those cods\n");
    std::string result = irRestHandler.Get("dem bones");
    printf("Retrieved those cods %s\n", result.c_str());
    if (result.empty())
    {
        messageLogger.Log("log that nothing was received");
    }
}