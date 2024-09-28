#include <iostream>
#include "api\http_request_router_tests.h"
#include "api/api_actions/home_display_action_tests.h"
#include "api/api_actions/raw_display_action_tests.h"
#include "api/api_actions/codes_display_action_tests.h"
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
#include "tools\BlinkerTests.h"
#include "transmit/IrSignalSenderTests.h"

int main()
{
    HttpRequestRouterTests().RunTests();
    HomeDisplayActionTests().RunTests();
    RawDisplayActionTests().RunTests();
    CodesDisplayActionTests().RunTests();
    LogsDisplayActionTests().RunTests();
    PlayIrActionTests().RunTests();
    CodeDisplayFormatterTests().RunTests();
    CodesRepositoryTests().RunTests();
    GPIOTests().RunTests();
    PicoScopeTests().RunTests();
    TraceDataFormatterTests().RunTests();
    PicoScopeCaptureAndPostTests().RunTests();
    RestHandlerTests().RunTests();
    TcpRequestMakerTests().RunTests();
    TcpResponseAnalyserTests().RunTests();
    HttpResponsePackagerTests().RunTests();
    MessageLoggerTests().RunTests();
    BlinkerTests().RunTests();
    IrSignalSenderTests().RunTests();
    std::cout << "Tests Complete\n";
}
