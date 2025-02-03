#include "hw_if/pico_hardware_interface.h"
#include "wifi/WiFiConnector.h"
#include "../rest/tcp_response_analyser.h"
#include "../rest/rest_handler.h"
#include "../rest/tcp_request_error_logger.h"
#include "../rest/tcp_request_maker.h"

int main()
{

    IHardwareInterface* _hw_if = new PicoHardwareInterface();
    IHardwareInterface& hw_if = *_hw_if;
    hw_if.initialise_pico_stdio(true);
    hw_if.set_led(true);
    printf("Start..\n");

    WiFiConnector* wifi = new WiFiConnector();
    wifi->ConnectToWiFi(hw_if, "Button", "12345678");
    printf("Co co connected\n");


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



    std::string response;
    int result = hw_if.tcp_request("192.168.1.126", 5001, "/currenttrack", response);

    printf("Result = %d\n", result);

    printf("Ended..\n");
}