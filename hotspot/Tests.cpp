#include <iostream>
#include "Tests\LedConfigurationTests.h"
#include "Tests\HotSpotConfigurationTests.h"
#include "Tests\HtmlRendererTests.h"
#include "Tests\FormRendererTests.h"

int main()
{
    (new LedConfigurationTests())->RunTests();
    (new HotSpotConfigurationTests())->RunTests();
    (new HtmlRendererTests())->RunTests();
    (new FormRendererTests())->RunTests();
    std::cout << "Tests Complete\n";
}
