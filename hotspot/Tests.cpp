#include <iostream>
#include "Tests\configurations\LedConfigurationTests.h"
#include "Tests\configurations\HotSpotConfigurationTests.h"
#include "Tests\logic\input_form\HtmlRendererTests.h"
#include "Tests\logic\input_form\InputFormRendererTests.h"
#include "Tests\logic\connecting\WIFIConnectorTests.h"
#include "Tests\logic\credentials\CredentialsHandlerTests.h"
#include "Tests\logic\credentials\PercentDecoderTests.h"
#include "Tests\logic\flash\FlashManagerTests.h"
#include "Tests\logic\flash\LoggerTests.h"

int main()
{
    LedConfigurationTests().RunTests();
    HotSpotConfigurationTests().RunTests();
    HtmlRendererTests().RunTests();
    InputFormRendererTests().RunTests();
    WIFIConnectorTests().RunTests();
    CredentialsHandlerTests().RunTests();
    FlashManagerTests().RunTests();
    PercentDecoderTests().RunTests();
    LoggerTests().RunTests();
    std::cout << "Tests Complete\n";
}
