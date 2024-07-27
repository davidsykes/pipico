#include <iostream>
#include "Tests\configurations\HotSpotConfigurationTests.h"
#include "Tests\logic\input_form\HtmlRendererTests.h"
#include "Tests\logic\input_form\InputFormRendererTests.h"
#include "Tests\logic\connecting\WIFIConnectorTests.h"
#include "Tests\logic\credentials\CredentialsHandlerTests.h"
#include "Tests\logic\credentials\PercentDecoderTests.h"
#include "Tests\logic\flash\FlashManagerTests.h"
#include "Tests\gpio\GPIOTests.h"
#include "Tests\pico_scope\PicoScopeTests.h"
#include "Tests\pico_scope\TraceDataFormatterTests.h"
#include "Tests\rest\RestHandlerTests.h"
#include "Tests\rest\TcpResponseAnalyserTests.h"

int main()
{
    HotSpotConfigurationTests().RunTests();
    HtmlRendererTests().RunTests();
    InputFormRendererTests().RunTests();
    WIFIConnectorTests().RunTests();
    CredentialsHandlerTests().RunTests();
    FlashManagerTests().RunTests();
    PercentDecoderTests().RunTests();
    GPIOTests().RunTests();
    PicoScopeTests().RunTests();
    RestHandlerTests().RunTests();
    TraceDataFormatterTests().RunTests();
    TcpResponseAnalyserTests().RunTests();
    std::cout << "Tests Complete\n";
}
