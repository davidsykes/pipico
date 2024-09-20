//#include <stdio.h>
#include "pico_scope_capture_and_post.h"
//#include "rest_handler.h"
//#include "tcp_response_analyser.h"
//#include "pico_scope.h"
//
//#define SCOPE_API_SERVER_IP "192.168.1.87"
//#define SCOPE_API_PORT 5000
//#define TRACE_DATA_CREATE_URL "/trace"
//#define PIN_FOR_PULL_UP 5
//


void PicoScopeCaptureAndPost::CaptureAndPost()
{
	hw_if.set_led(1);
	PicoScopeTrace& trace = pico_scope.FetchTrace();
	hw_if.set_led(0);
	std::string trace_data = trace_data_formatter.FormatTraceData(trace);
	rest_handler.Put("/trace", trace_data.c_str());
}


//void RunScope(IHardwareInterface& hw_if)
//{
//    TcpResponseAnalyser tcpResponseAnalyser;
//    TcpRequestErrorLogger tcpRequestErrorLogger;
//    TcpRequestMaker tcpRequestMaker(
//        SCOPE_API_SERVER_IP,
//        SCOPE_API_PORT,
//        hw_if,
//        tcpResponseAnalyser,
//        tcpRequestErrorLogger);
//    RestHandler restHandler(tcpRequestMaker);
//    PicoScopeConfiguration ir_scope_configuration(PIN_FOR_PULL_UP);
//    PicoScopeRecordAndPost srap(
//        hw_if,
//        ir_scope_configuration,
//        restHandler);
//    ((IPicoScopeRecordAndPost&)srap).RecordAndPostTrace();
//
//   // ??? PicoScopeRecorder picoScopeRecorder(hw_if, ir_scope_configuration);
//   // ??? RecordIrAction recordIrAction(picoScopeRecorder);
//}
//
//std::string PicoScopeRecordAndPost::RecordAndPostTrace()
//{
//    printf("RECORD AND POST\n");
//    run_scope(hw_if, config, restHandler);
//    return "RECORD AND POST";
//}
//
//void run_scope(IHardwareInterface& hw_if, PicoScopeConfiguration& config, IRestHandler& rest)
//{
//    printf("Run scope on GP4-7 with pull up on pin %d\n", config.pin);
//
//    hw_if.initialise_input_pin(config.pin);
//    hw_if.gpio_set_pull_up(config.pin, 1);
//
//    //TcpResponseAnalyser tcpResponseAnalyser;
//    //RestHandler rest_imp(hw_if,
//    //                 tcpResponseAnalyser,
//    //                 SCOPE_API_SERVER_IP, SCOPE_API_PORT);
//    //IRestHandler& rest = rest_imp;
//    PicoScope scope(hw_if, 100000);
//    TraceDataFormatter traceFormatter;
//
//    //while(1)
//    {
//        hw_if.set_led(1);
//        PicoScopeTrace& trace = scope.FetchTrace();
//
//        hw_if.set_led(0);
//        std::string traceData = traceFormatter.FormatTraceData(trace);
//        std::string result = rest.Put(TRACE_DATA_CREATE_URL, traceData.c_str());
//        printf("Scope result %s\n", result.c_str());
//        if (result != "Ok")
//        {
//            //rest.Log();
//        }
//    }
//}
//
