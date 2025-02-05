#include <iostream>
#include "pico_scope/PicoScopeTests.h"
#include "pico_scope/TraceDataFormatterTests.h"
#include "pico_scope/PicoScopeCaptureAndPostTests.h"
#include "tools\BlinkerTests.h"


int main()
{
    std::cout << "Hello World!\n";
    PicoScopeTests().RunTests();
    TraceDataFormatterTests().RunTests();
    PicoScopeCaptureAndPostTests().RunTests();
    BlinkerTests().RunTests();
}
