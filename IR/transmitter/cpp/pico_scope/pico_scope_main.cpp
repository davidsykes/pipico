#include "../hw_if/pico_hardware_interface.h"
#include "pico_scope_main.h"
#include "pico_scope_configuration.h"
#include "pico_scope_capture_and_post.h"
#include "../rest/tcp_response_analyser.h"
#include "../rest/rest_handler.h"
#include "../rest/tcp_request_error_logger.h"
#include "../rest/tcp_request_maker.h"

#define SCOPE_API_SERVER_IP "192.168.1.87"
#define SCOPE_API_PORT 5000
#define TRACE_DATA_CREATE_URL "/trace"
#define PIN_FOR_PULL_UP 5


void pico_scope_main(IHardwareInterface& hw_if)
{
    printf("Build scope objects\n");
    TcpResponseAnalyser tcpResponseAnalyser;
    TcpRequestErrorLogger tcpRequestErrorLogger;
    TcpRequestMaker tcpRequestMaker(
        SCOPE_API_SERVER_IP,
        SCOPE_API_PORT,
        hw_if,
        tcpResponseAnalyser,
        tcpRequestErrorLogger);
    TraceDataFormatter trace_data_formatter;
    RestHandler restHandler(tcpRequestMaker);
    PicoScopeConfiguration ir_scope_configuration(PIN_FOR_PULL_UP);
    hw_if.initialise_input_pin(ir_scope_configuration.pin);
    hw_if.gpio_set_pull_up(ir_scope_configuration.pin, 1);

    PicoScope scope(hw_if, 2000000);
    PicoScopeCaptureAndPost srap(
        hw_if,
        scope,
        trace_data_formatter,
        restHandler,
        TRACE_DATA_CREATE_URL);
    while(true)
    {
        printf("Capture a trace\n");
        ((IPicoScopeCaptureAndPost&)srap).CaptureAndPost();
    }
}
