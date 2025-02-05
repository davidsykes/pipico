#include "RestLibraryTests.h"
#include "RestHandlerTests.h"
#include "TcpRequestMakerTests.h"
#include "TcpResponseAnalyserTests.h"

void RestLibraryTests::RunTests()
{
    RestHandlerTests().RunTests();
    TcpRequestMakerTests().RunTests();
    TcpResponseAnalyserTests().RunTests();
}

