#include <iostream>
#include "Tests\LedConfigurationTests.h"
#include "Tests\HotSpotConfigurationTests.h"

int main()
{
    ITestModule* lt = new LedConfigurationTests();
    lt->RunTests();
    lt = new HotSpotConfigurationTests();
    lt->RunTests();
    std::cout << "Tests Complete\n";
}
