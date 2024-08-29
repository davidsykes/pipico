#include <iostream>
//#include "Tests\configurations\HotSpotConfigurationTests.h"
//#include "Tests\logic\input_form\HtmlRendererTests.h"
//#include "Tests\logic\input_form\InputFormRendererTests.h"
//#include "Tests\logic\connecting\WIFIConnectorTests.h"
//#include "Tests\logic\credentials\CredentialsHandlerTests.h"
//#include "Tests\logic\credentials\PercentDecoderTests.h"
//#include "Tests\logic\flash\FlashManagerTests.h"
//#include "Tests\gpio\GPIOTests.h"
//#include "Tests\pico_scope\PicoScopeTests.h"
//#include "Tests\pico_scope\TraceDataFormatterTests.h"
//#include "Tests\rest\RestHandlerTests.h"
//#include "Tests\rest\TcpRequestMakerTests.h"
//#include "Tests\rest\TcpResponseAnalyserTests.h"
//#include "Tests\ir\codes\ir_code_repository_tests.h"
//#include "Tests\ir\server\pages\HttpServerHomePageTests.h"
//#include "Tests\ir\server\http_server_record_handler_tests.h"
//#include "Tests\ir\server_responses\codes_record_request_handler_tests.h"
#include "api\http_request_router_tests.h"
//#include "Tests\ir\server\http_response_packager_tests.h"
//#include "Tests\ir\server\widgets\logs_display_widget_tests.h"
#include "tools\MessageLoggerTests.h"

int main()
{
    //HotSpotConfigurationTests().RunTests();
    //HtmlRendererTests().RunTests();
    //InputFormRendererTests().RunTests();
    //WIFIConnectorTests().RunTests();
    //CredentialsHandlerTests().RunTests();
    //FlashManagerTests().RunTests();
    //PercentDecoderTests().RunTests();
    //GPIOTests().RunTests();
    //PicoScopeTests().RunTests();
    //TcpRequestMakerTests().RunTests();
    //RestHandlerTests().RunTests();
    //TraceDataFormatterTests().RunTests();
    //TcpResponseAnalyserTests().RunTests();
    //IrCodeRepositoryTests().RunTests();
    //HttpServerHomePageTests().RunTests();
    //CodesRecordHandlerTests().RunTests();
    HttpRequestRouterTests().RunTests();
    //HttpResponsePackagerTests().RunTests();
    //HttpServerRecordHandlerTests().RunTests();
    MessageLoggerTests().RunTests();
    //LogsDisplayWidgetTests().RunTests();
    std::cout << "Tests Complete\n";
}
