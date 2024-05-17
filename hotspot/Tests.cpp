#include <iostream>
#include "Tests\LedConfigurationTests.h"
#include "Tests\HotSpotConfigurationTests.h"
#include "Tests\HtmlRendererTests.h"
#include "Tests\InputFormRendererTests.h"

int main()
{
    (new LedConfigurationTests())->RunTests();
    (new HotSpotConfigurationTests())->RunTests();
    (new HtmlRendererTests())->RunTests();
    (new InputFormRendererTests())->RunTests();
    std::cout << "Tests Complete\n";
}
