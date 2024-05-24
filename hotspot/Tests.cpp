#include <iostream>
#include "Tests\LedConfigurationTests.h"
#include "Tests\HotSpotConfigurationTests.h"
#include "Tests\logic\input_form\HtmlRendererTests.h"
#include "Tests\logic\input_form\InputFormRendererTests.h"
#include "Tests\logic\connecting\WIFIConnectorTests.h"

int main()
{
    (new LedConfigurationTests())->RunTests();
    (new HotSpotConfigurationTests())->RunTests();
    (new HtmlRendererTests())->RunTests();
    (new InputFormRendererTests())->RunTests();
    (new WIFIConnectorTests())->RunTests();
    std::cout << "Tests Complete\n";
}
