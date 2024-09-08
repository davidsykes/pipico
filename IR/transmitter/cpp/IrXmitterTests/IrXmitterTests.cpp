#include <iostream>
#include "api\http_request_router_tests.h"
#include "codes\CodesRepositoryTests.h"
#include "tcp_server/http_response_packager_tests.h"
#include "api/api_actions/logs_display_action_tests.h"
#include "tools\MessageLoggerTests.h"

int main()
{
    HttpRequestRouterTests().RunTests();
    HttpResponsePackagerTests().RunTests();
    MessageLoggerTests().RunTests();
    LogsDisplayActionTests().RunTests();
    CodesRepositoryTests().RunTests();
    std::cout << "Tests Complete\n";
}
