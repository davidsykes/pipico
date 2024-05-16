#include <iostream>
#include "Tests\LedConfigurationTests.h"
#include "Tests\HotSpotConfigurationTests.h"
#include "Tests\HtmlRendererTests.h"

int main()
{
    ITestModule* lt = new LedConfigurationTests();
    lt->RunTests();
    lt = new HotSpotConfigurationTests();
    lt->RunTests();
    (new HtmlRendererTests())->RunTests();
    std::cout << "Tests Complete\n";
}
