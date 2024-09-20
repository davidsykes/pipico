#include <iostream>
#include "api\http_request_router_tests.h"
#include "api/home_display_action_tests.h"
#include "api/codes_display_action_tests.h"
#include "api/api_actions/logs_display_action_tests.h"
#include "api/api_actions/play_ir_action_tests.h"
#include "api/formatters/code_display_fomatter_tests.h"
#include "codes\CodesRepositoryTests.h"
#include "gpio/GPIOTests.h"
#include "pico_scope/PicoScopeTests.h"
#include "pico_scope/TraceDataFormatterTests.h"
#include "pico_scope/PicoScopeCaptureAndPostTests.h"
#include "rest/RestHandlerTests.h"
#include "rest/TcpRequestMakerTests.h"
#include "rest/TcpResponseAnalyserTests.h"
#include "tcp_server/http_response_packager_tests.h"
#include "tools\MessageLoggerTests.h"
#include "transmit/IrSignalSenderTests.h"

int main()
{
    HttpRequestRouterTests().RunTests();
    HttpResponsePackagerTests().RunTests();
    MessageLoggerTests().RunTests();
    LogsDisplayActionTests().RunTests();
    CodesRepositoryTests().RunTests();
    HomeDisplayActionTests().RunTests();
    CodesDisplayActionTests().RunTests();
    CodeDisplayFormatterTests().RunTests();
    PlayIrActionTests().RunTests();
    IrSignalSenderTests().RunTests();
    GPIOTests().RunTests();
    RestHandlerTests().RunTests();
    TcpRequestMakerTests().RunTests();
    TcpResponseAnalyserTests().RunTests();
    PicoScopeTests().RunTests(); 
    TraceDataFormatterTests().RunTests();
    PicoScopeCaptureAndPostTests().RunTests();
    std::cout << "Tests Complete\n";
}
