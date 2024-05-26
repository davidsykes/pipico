#include <iostream>
#include "Tests\LedConfigurationTests.h"
#include "Tests\HotSpotConfigurationTests.h"
#include "Tests\logic\input_form\HtmlRendererTests.h"
#include "Tests\logic\input_form\InputFormRendererTests.h"
#include "Tests\logic\connecting\WIFIConnectorTests.h"
#include "Tests\logic\credentials\CredentialsHandlerTests.h"
#include "Tests\logic\FlashManagerTests.h"

int main()
{
    (new LedConfigurationTests())->RunTests();
    (new HotSpotConfigurationTests())->RunTests();
    (new HtmlRendererTests())->RunTests();
    (new InputFormRendererTests())->RunTests();
    (new WIFIConnectorTests())->RunTests();
    (new CredentialsHandlerTests())->RunTests();
    (new FlashManagerTests())->RunTests();
    std::cout << "Tests Complete\n";
}
