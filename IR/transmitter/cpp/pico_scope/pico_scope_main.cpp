

//#define SCOPE_API_SERVER_IP "192.168.1.87"
//#define SCOPE_API_PORT 5000
//#define TRACE_DATA_CREATE_URL "/trace"
//#define PIN_FOR_PULL_UP 5


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
    RestHandler restHandler(tcpRequestMaker);
    PicoScopeConfiguration ir_scope_configuration(PIN_FOR_PULL_UP);
   hw_if.initialise_input_pin(config.pin);
   hw_if.gpio_set_pull_up(config.pin, 1);

    PicoScopeCaptureAndPost srap(
        hw_if,
        ir_scope_configuration,
        restHandler);

    printf("Capture a trace\n");
    ((PicoScopeCaptureAndPost&)srap).RecordAndPostTrace();

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

}