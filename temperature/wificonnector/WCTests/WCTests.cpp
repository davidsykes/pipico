
#include <iostream>
#include "HotSpotRequestRouterTests.h"
#include "flash/FlashParametersReaderTests.h"
#include "flash/FlashWriterTests.h"
#include "input_form/HtmlRendererTests.h"
#include "input_form/InputFormRendererTests.h"
#include "input_form/PercentDecoderTests.h"
#include "input_form/SSIDPasswordInputFormRendererTests.h"
#include "input_form/SSIDPasswordSubmitterTests.h"
#include "tcpserver/http_response_packager_tests.h"

int main()
{
    HotSpotRequestRouterTests().RunTests();
    FlashParametersReaderTests().RunTests();
    FlashWriterTests().RunTests();
    HtmlRendererTests().RunTests();
    InputFormRendererTests().RunTests();
    PercentDecoderTests().RunTests();
    SSIDPasswordInputFormRendererTests().RunTests();
    SSIDPasswordSubmitterTests().RunTests();
    HttpResponsePackagerTests().RunTests();
    std::cout << "Tests Run\n";
}