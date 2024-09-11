#include <iostream>
#include "api\http_request_router_tests.h"
#include "api/home_display_action_tests.h"
#include "api/codes_display_action_tests.h"
#include "api/api_actions/logs_display_action_tests.h"
#include "api/api_actions/play_ir_action_tests.h"
#include "api/formatters/code_display_fomatter_tests.h"
#include "codes\CodesRepositoryTests.h"
#include "tcp_server/http_response_packager_tests.h"
#include "tools\MessageLoggerTests.h"

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
    std::cout << "Tests Complete\n";
}
