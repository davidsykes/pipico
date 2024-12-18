#include <iostream>
#include "api\ir_controller_http_request_router_tests.h"
#include "api/api_actions/home_display_action_tests.h"
#include "api/api_actions/raw_display_action_tests.h"
#include "api/api_actions/codes_display_action_tests.h"
#include "api/api_actions/code_sequences_display_action_tests.h"
#include "api/api_actions/logs_display_action_tests.h"
#include "api/api_actions/play_ir_code_action_tests.h"
#include "api/api_actions/play_ir_sequence_action_tests.h"
#include "api/formatters/code_display_fomatter_tests.h"
#include "api/formatters/button_formatter_tests.h"
#include "codes\CodesRepositoryTests.h"
#include "codes/CodeSequenceRepositoryTests.h"
#include "gpio/GPIOTests.h"
#include "tools\MessageLoggerTests.h"
#include "transmit/IrCodeSenderTests.h"
#include "transmit/IrSequenceSenderTests.h"
#include "wifi/HotSpotRequestRouterTests.h"
#include "wifi/flash/FlashWriterTests.h"
#include "wifi/flash/FlashParametersReaderTests.h"
#include "wifi/tcpserver/http_response_packager_tests.h"
#include "wifi/input_form/HtmlRendererTests.h"
#include "wifi/input_form/InputFormRendererTests.h"
#include "wifi/input_form/SSIDPasswordInputFormRendererTests.h"
#include "wifi/input_form/SSIDPasswordSubmitterTests.h"
#include "wifi/input_form/PercentDecoderTests.h"

int main()
{
    IrControllerHttpRequestRouterTests().RunTests();
    HomeDisplayActionTests().RunTests();
    RawDisplayActionTests().RunTests();
    CodesDisplayActionTests().RunTests();
    CodeSequencesDisplayActionTests().RunTests();
    LogsDisplayActionTests().RunTests();
    PlayIrCodeActionTests().RunTests();
    PlayIrSequenceActionTests().RunTests();
    CodeDisplayFormatterTests().RunTests();
    ButtonFormatterTests().RunTests();
    CodesRepositoryTests().RunTests();
    CodeSequenceRepositoryTests().RunTests();
    GPIOTests().RunTests();
    MessageLoggerTests().RunTests();
    IrCodeSenderTests().RunTests();
    IrSequenceSenderTests().RunTests();
    HotSpotRequestRouterTests().RunTests();
    FlashWriterTests().RunTests();
    FlashParametersReaderTests().RunTests();
    HttpResponsePackagerTests().RunTests();
    HtmlRendererTests().RunTests();
    InputFormRendererTests().RunTests();
    SSIDPasswordInputFormRendererTests().RunTests();
    SSIDPasswordSubmitterTests().RunTests();
    PercentDecoderTests().RunTests();
    std::cout << "Tests Complete\n";
}
