#include "stdio.h"
#include "ir_code_repository.h"

void IrCodeRepository::RetrieveCodes()
{
    printf("Retrieve those cods\n");
    std::string result = irRestHandler.Get("dem bones");
    printf("Retrieve those cods %s\n", result.c_str());
}