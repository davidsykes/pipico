#include <iostream>
#include "api\http_request_router_tests.h"
#include "tcp_server/http_response_packager_tests.h"
#include "tools\MessageLoggerTests.h"

int main()
{
    HttpRequestRouterTests().RunTests();
    HttpResponsePackagerTests().RunTests();
    MessageLoggerTests().RunTests();
    std::cout << "Tests Complete\n";
}
